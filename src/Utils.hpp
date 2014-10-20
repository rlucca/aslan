#pragma once

/**
	\brief Append the nulled-terminated string `second' to the end of
	the nulled-terminated string `first'. A string can contain delimiters
	that need be changed to other. If so `changeDelimiter' will hold the
	new delimiter. If it is zero the data is copied as it.


	\param [in] first, nulled-based string to be append
	\param [in] second, nulled-based string to append
	\param [in] changeDelimiter, new delimiter representation

	\return new nulled-based string and free both strings
*/
char *lexema_append(char *first,
					char *second,
					char changeDelimiter = 0);

/**
	\brief Append the nulled-terminated string `second' to the end of
	the nulled-terminated string `first' in a new nulled-terminated
	string. It does not touch `first' or `second'.

	\param [in] first, nulled-based string to be append
	\param [in] second, nulled-based string to append

	\return a new nulled-terminated string without free the parameters
*/
char *lexema_cat(char *first, char *second);
