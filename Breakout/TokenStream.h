/*
    Beginning DirectX 11 Game Programming
    By Allen Sherrod and Wendy Jones

    TokenStream - Used to return blocks of text in a file.
*/


#pragma once

#include <string>

class TokenStream
{
   public:
      TokenStream( );

      void ResetStream( );

      void SetTokenStream( char* data );
      bool GetNextToken( std::string* buffer, char* delimiters, int totalDelimiters );
      bool MoveToNextLine( std::string *buffer );

   private:
      int startIndex_, endIndex_;
      std::string data_;
};
