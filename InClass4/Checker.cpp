#include "Checker.h"

Checker::Checker()
{
	name = "";
	avatar = "";
}
Checker::Checker( string name, string avatar )
{
	this->name = name;
	this->avatar = avatar;
}
void Checker::setName( string newName )
{
	name = newName;
}
void Checker::setAvatar( string newAvatar )
{
	avatar = newAvatar;
}
string Checker::getName()
{
	return name;
}
string Checker::getAvatar()
{
	return avatar;
}

bool Checker::operator==( const Checker& rhs ) 
{
	return (name == rhs.name && avatar == rhs.avatar );
}
