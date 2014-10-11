#pragma once

/**
	\brief Append the nulled-terminated string `second' to the end of
	the nulled-terminated string `first'. A string can contain delimiters
	that need be changed to other. If so `changeDelimiter' will hold the
	new delimiter. If it is zero the data is copied as it.


	\param [in] first, nulled-based string to be append
	\param [in] second, nulled-based string to append
	\param [in] changeDelimiter, new delimiter representation

	\return new nulled-based string and free on both strings
*/
char *lexema_append(char *first,
					char *second,
					char changeDelimiter = 0);
