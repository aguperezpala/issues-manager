/*
 * Configuration.h
 *
 * We gonna use the next syntaxes to the KEYs:
 * KEY_NAME ++ "_" ++ <VALUE_TYPE>
 * where <VALUE_TYPE>: 	STR 	(indicating that its a string value)
 * 						INT 	(indicating that its a int value)
 * 						DOUBLE 	(indicating that its a double value)
 *
 * This is to easily identify the kind of the value to parse.
 *
 *  Created on: 31/10/2010
 *      Author: agustin
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "debug.h"


/* We will use 3 defines to parse a configuration file. These are the
 * equal character, the comment character and the end string. The first one it
 * will be the character who divide the KEY_NAME of the VALUE_NAME
 * (the generally the = character). The second one will be used to specifies the
 * comments lines which will be skipped when read it, and the third one, it will
 * determine the end of the value (generally the '\n')
 */
#define CONF_EQ_CHAR		'='
#define CONF_COMMENT_CHAR	'#'
#define CONF_END_STR		"\n"


class Configuration {
public:
	// empty constructor
	Configuration(const std::string &confName = ""): _name(confName){};

	// set/get the conf Name
	void setConfigName(const std::string &cName){_name = cName;};
	const std::string &getConfigName(void){return _name;};

	/* Load configuration from file.
	 * REQUIRES:
	 * 		fname (path to the filename)
	 * RETURNS:
	 * 		< 0 on error
	 * 		0	if success
	 */
	int loadFromFile(const std::string &fname);

	/* Save the configuration to a specific file
	 * REQUIRES:
	 * 		fname (path to the filename)
	 * RETURNS:
	 * 		errCode
	 */
	int saveToFile(const std::string &fname);

	/* Here we will add useful functions to retrieve different kinds of values
	 * In all cases it will be returned true if success or false if not
	 * REQUIRES:
	 * 		key		the value key
	 * 		value	[OUT], where it will be returned the value
	 * RETURNS:
	 * 		true 	if success
	 * 		false 	otherwise
	 */
	bool getValue(const std::string &key, int &value);
	bool getValue(const std::string &key, std::string &value);
	bool getValue(const std::string &key, double &value);

	/* Add new value to the configuration
	 * REQUIRES:
	 * 		key		The keyName of the value (NOTE: if the key exists the value
	 * 										  is replaced)
	 * 		value	the value associated
	 * RETURNS:
	 * 		errCode
	 */
	int setNewValue(const std::string &key, const int &value);
	int setNewValue(const std::string &key, const std::string &value);
	int setNewValue(const std::string &key, const double &value);

	/* Check if exists some key (value) in the configuration
	 * RETURNS:
	 * 		true	if exists
	 * 		false	otherwise
	 */
	bool exists(const std::string &key);


	// empty destructor
	~Configuration();

private:

	/*						FUNCTIONS						*/

	/* Function used to read a file
	 * RETURNS:
	 * 	errCode
	 */
	int readFileContent(const std::string &fname, std::string &content);

	/* Function which create a list of lines to be parsed which contains the
	 * the two Characters, the equal and the end char.
	 * RETURNS:
	 * 		numLines	the number of lines to be parsed
	 */
	int getLinesToBeParsed(const std::string &content,
			std::list<std::string> &lines);

	/* Retrieve the keyname and the value associated from a line, using the
	 * delimiters defined before.
	 * REQUIRES:
	 * 		line	to be parsed
	 * 		key		[OUT] keyName parsed
	 * 		value	[OUT] value of the keyName
	 * RETURNS:
	 * 		errCode
	 */
	int parseLine(const std::string &line, std::string &key, std::string &value);


	/*						MEMBERS							*/
	// configuration Name
	std::string _name;
	// we will map the values in a hash <KEY_NAME, VALUE>
	std::map<std::string, std::string> _values;

};

#endif /* CONFIGURATION_H_ */
