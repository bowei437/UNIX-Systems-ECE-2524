#ifndef CHECKER_H
#define CHECKER_H

#include <string>
using std::string;
/**
This is a simple class that represents a checker for the connect 4 game.  It 
could be modified to be a checker for almost any game.
*/
class Checker
{
private:
	/**
	This is the players name.  I'm not really sure why I have this here.
	*/
	string name;
	/**
	This is the avatar for the player.  Right now, it's just a character and it's what's displayed in the display board method.
	But it could be fancier, like an image, etc.
	*/
	string avatar;
public:
	/**
	This is the default constructor.  It simply creates a Checker with both the name and avatar fields to be ""
	*/
	Checker();
	/**
	This is a parameterized constructor.  It allows you to create a Checker with the given name and avatar fields set.
	Don't forget, these parameters will shadow the fields.
	@param name - a string that is the name of the person who is using this checker
	@param avatar - a string that is the avatar for this person
	*/
	Checker( string name, string avatar );

	/**
	This will update the name of the player
	@param newName - the name of the player
	*/
	void setName( string newName );
	/**
	This will update the avatar for the player
	@param newAvatar - the new avatar for the player
	*/
	void setAvatar( string newAvatar );
	/**
	This will get the name of the Checker
	@return the name
	*/
	string getName();
	/**
	This will return the avatar of the Checker
	@return the avatar
	*/
	string getAvatar();
	/**
	This will return true if the name and the avatar of both Checkers is the same.  This could be useful for checking to see if a Checker is "blank"
	@return True if the name and avatar of both checkers is the same and false otherwise
	*/
	bool operator==( const Checker& rhs );
};

#endif
