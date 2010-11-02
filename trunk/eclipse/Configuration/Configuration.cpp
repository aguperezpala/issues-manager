/*
 * Configuration.cpp
 *
 *  Created on: 31/10/2010
 *      Author: agustin
 */

#include "Configuration.h"

/*						PRIVATE FUNCTIONS						*/

/* Function used to read a file
 * RETURNS:
 * 	errCode
 */
int Configuration::readFileContent(const std::string &fname, std::string &content)
{
	int length = 0;
	char *buffer = NULL;
	std::ifstream is;


	is.open (fname.c_str(), std::ios::binary);
	if(!is.good()){
		debug("The file does not exists %s\n", fname.c_str());
		return -1;
	}


	// get length of file:
	is.seekg (0, std::ios::end);
	length = is.tellg();
	is.seekg (0, std::ios::beg);

	// allocate memory:
	buffer = new char[length];

	if(buffer == NULL) {
		debug("Cannot allocate\n");
		return -2;
	}

	// read data as a block:
	is.read(buffer,length);
	is.close();

	content = buffer;

	delete[] buffer;

	return 0;
}

/* Function which create a list of lines to be parsed which contains the
 * the two Characters, the equal and the end char.
 * RETURNS:
 * 		numLines	the number of lines to be parsed
 */
int Configuration::getLinesToBeParsed(const std::string &content,
		std::list<std::string> &lines)
{
	size_t bPos = 0, ePos = 0;
	size_t len = 0;
	std::string endStr = CONF_END_STR;
	std::string auxStr;

	lines.clear();

	while(bPos != std::string::npos && ePos != std::string::npos) {
		ePos = content.find(endStr, bPos);
		if(ePos == std::string::npos)
			break;

		// check if is a comment
		if(content[bPos] == CONF_COMMENT_CHAR) {
			// updates the positions
			bPos = ePos + endStr.length();
			continue;
		}

		// if we are here then we have to verify if the substr contains the
		// CONF_EQ_CHAR
		len = ePos - bPos;
		auxStr = content.substr(bPos, len);
		bPos = ePos + endStr.size();

		if(auxStr.find(CONF_EQ_CHAR) == std::string::npos)
			// we cannot find, so we dont add this string to the list
			continue;

		lines.push_back(auxStr);
	}

	return lines.size();
}

/* Retrieve the keyname and the value associated from a line, using the
 * delimiters defined before.
 * REQUIRES:
 * 		line	to be parsed
 * 		key		[OUT] keyName parsed
 * 		value	[OUT] value of the keyName
 * RETURNS:
 * 		errCode
 */
int Configuration::parseLine(const std::string &line, std::string &key,
		std::string &value)
{
	size_t eqPos = 0;

	if((&line == NULL) || (&key == NULL) || (&value == NULL)) {
		debug("Bad args received\n");
		return -1;
	}

	// now Parse the values
	eqPos = line.find(CONF_EQ_CHAR);
	if(eqPos == std::string::npos) {
		debug("Cannot find the eqPos\n");
		return -2;
	}

	key = line.substr(0, eqPos);
	value = line.substr(eqPos + 1, line.size() - eqPos - 1);

	return 0;
}


/*						PUBLIC	FUNCTIONS						*/

/* Load configuration from file.
 * REQUIRES:
 * 		fname (path to the filename)
 * RETURNS:
 * 		< 0 on error
 * 		0	if success
 */
int Configuration::loadFromFile(const std::string &fname)
{
	std::string fileContent;
	std::list<std::string> lines;
	std::string key, value;
	std::list<std::string>::iterator it;

	if(readFileContent(fname, fileContent) < 0) {
		debug("Could not read the file\n");
		return -1;
	}

	// clear the actual map
	_values.clear();

	if (getLinesToBeParsed(fileContent, lines) <= 0) {
		debug("No lines could be parsed from the ConfigFile\n");
		return -1;
	}

	for(it = lines.begin(); it != lines.end(); ++it) {
		if(parseLine(*it, key, value) < 0) {
			debug("Problem parsing: %s\n", (*it).c_str());
			continue;
		}
		// if we are here then we have to add the pair key, value to the map
		_values[key] = value;
		key = value = "";
	}

	return 0;
}


/* Save the configuration to a specific file
 * REQUIRES:
 * 		fname (path to the filename)
 * RETURNS:
 * 		errCode
 */
int Configuration::saveToFile(const std::string &fname)
{
	std::ofstream ostream;
	std::map<std::string, std::string>::iterator it;

	ostream.open(fname.c_str(), std::ios::binary);

	if(!ostream.good()) {
		debug("Could not open the file to write\n");
		return -1;
	}

	for(it = _values.begin(); it != _values.end(); ++it) {
		ostream << (*it).first << CONF_EQ_CHAR << (*it).second << CONF_END_STR;
	}

	ostream.close();

	return 0;
}

/* Here we will add useful functions to retrieve different kinds of values
 * In all cases it will be returned true if success or false if not
 * REQUIRES:
 * 		key		the value key
 * 		value	[OUT], where it will be returned the value
 * RETURNS:
 * 		true 	if success
 * 		false 	otherwise
 */
bool Configuration::getValue(const std::string &key, int &value)
{
	std::stringstream ss;

	ss << _values[key];
	ss >> value;

	if(ss.fail())
		return false;

	return true;
}

bool Configuration::getValue(const std::string &key, std::string &value)
{
	value = _values[key];
	return true;
}

bool Configuration::getValue(const std::string &key, double &value)
{
	std::stringstream ss;

	ss << _values[key];
	ss >> value;

	if(ss.fail())
		return false;

	return true;
}

/* Add new value to the configuration
 * REQUIRES:
 * 		key		The keyName of the value (if the key Exists => replace the value)
 * 		value	the value associated
 * RETURNS:
 * 		errCode
 */
int Configuration::setNewValue(const std::string &key, const int &value)
{
	std::stringstream ss;

	ss << value;

	if(ss.fail())
			return -1;

	_values[key] = ss.str();

	return 0;
}

int Configuration::setNewValue(const std::string &key, const std::string &value)
{
	_values[key] = value;

	return 0;
}

int Configuration::setNewValue(const std::string &key, const double &value)
{
	std::stringstream ss;

	ss << value;

	if(ss.fail())
			return -1;

	_values[key] = ss.str();

	return 0;
}


/* Check if exists some key (value) in the configuration
 * RETURNS:
 * 		true	if exists
 * 		false	otherwise
 */
bool Configuration::exists(const std::string &key)
{
	return (_values.find(key) != _values.end());
}

/* Removes a value from the configuration */
void Configuration::removeValue(const std::string &key)
{
	_values.erase(key);
}


Configuration::~Configuration() {
	// TODO Auto-generated destructor stub
}
