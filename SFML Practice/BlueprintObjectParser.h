#pragma once
#include "GameObjectBlueprint.h"
#include <string>

using namespace std;

class BlueprintObjectParser 
{
private:
	/* The extractStringBetweenTags private function will capture the content between two tags. The parameters are three
	string instances. The first string is a full line of text from level1.txt, while the second and third are the start and
	end tags, which need to be discarded. The text between the two tags is then returned to the calling code. */
	string extractStringBetweenTags(string stringToSearch, string startTag, string endTag);

public:
	/* Ifstream is used to read from the file. The second parameter is a reference to a GameObjectBlueprint instance. The
	function will populate the GameObjectBlueprint instance with the values that were read from the level1.txt file, which
	can then be used back in the calling code to create an actual GameObject */
	void parseNextObjectForBlueprint(ifstream& reader, GameObjectBlueprint& bp);
};