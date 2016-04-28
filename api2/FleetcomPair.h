//  Copyright (C) 2004-2008, Robotics Equipment Corporation GmbH

//Copyright (c) ...
//
//REC Robotics Equipment Corporation GmbH, Planegg, Germany. All rights reserved.
//Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//
//THIS SOFTWARE IS PROVIDED BY REC ROBOTICS EQUIPMENT CORPORATION GMBH ï¿½AS ISï¿½ AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL REC ROBOTICS EQUIPMENT CORPORATION GMBH
//BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
//GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
//LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//Copyright (c) ...
//
//REC Robotics Equipment Corporation GmbH, Planegg, Germany. Alle Rechte vorbehalten.
//Weiterverbreitung und Verwendung in nichtkompilierter oder kompilierter Form, mit oder ohne Verï¿½nderung, sind unter den folgenden Bedingungen zulï¿½ssig:
//1) Weiterverbreitete nichtkompilierte Exemplare mï¿½ssen das obige Copyright, diese Liste der Bedingungen und den folgenden Haftungsausschluss im Quelltext enthalten.
//2) Weiterverbreitete kompilierte Exemplare mï¿½ssen das obige Copyright, diese Liste der Bedingungen und den folgenden Haftungsausschluss in der Dokumentation und/oder anderen Materialien, die mit dem Exemplar verbreitet werden, enthalten.
//
//DIESE SOFTWARE WIRD VON REC ROBOTICS EQUIPMENT CORPORATION GMBH OHNE JEGLICHE SPEZIELLE ODER IMPLIZIERTE GARANTIEN ZUR VERFÜGUNG GESTELLT, DIE UNTER
//ANDEREM EINSCHLIESSEN: DIE IMPLIZIERTE GARANTIE DER VERWENDBARKEIT DER SOFTWARE FÜR EINEN BESTIMMTEN ZWECK. AUF KEINEN FALL IST REC ROBOTICS EQUIPMENT CORPORATION GMBH
//FÜR IRGENDWELCHE DIREKTEN, INDIREKTEN, ZUFÄLLIGEN, SPEZIELLEN, BEISPIELHAFTEN ODER FOLGESCHÄDEN (UNTER ANDEREM VERSCHAFFEN VON ERSATZGÜTERN ODER -DIENSTLEISTUNGEN;
//EINSCHRÄNKUNG DER NUTZUNGSFÄHIGKEIT; VERLUST VON NUTZUNGSFÄHIGKEIT; DATEN; PROFIT ODER GESCHÄFTSUNTERBRECHUNG), WIE AUCH IMMER VERURSACHT UND UNTER WELCHER VERPFLICHTUNG
//AUCH IMMER, OB IN VERTRAG, STRIKTER VERPFLICHTUNG ODER UNERLAUBTER HANDLUNG (INKLUSIVE FAHRLÄSSIGKEIT) VERANTWORTLICH, AUF WELCHEM WEG SIE AUCH IMMER DURCH DIE BENUTZUNG
//DIESER SOFTWARE ENTSTANDEN SIND, SOGAR, WENN SIE AUF DIE MÖGLICHKEIT EINES SOLCHEN SCHADENS HINGEWIESEN WORDEN SIND.

#ifndef _REC_ROBOTINO_API2_FLEETCOMPAIR_H_
#define _REC_ROBOTINO_API2_FLEETCOMPAIR_H_

#include <string.h>

namespace rec
{
	namespace robotino
	{
		namespace api2
		{
			class FleetcomPair
			{
			public:
				typedef enum
				{
					NoType,
					StringType,
					IntType,
					FloatType
				} Type;

				FleetcomPair()
					: _type( NoType )
					, _key( NULL )
					, _strValue( NULL )
					, _intValue( 0 )
					, _floatValue( 0.0 )
				{
				}

				FleetcomPair( const char* key, const char* value )
					: _type( NoType )
					, _key( NULL )
					, _strValue( NULL )
					, _intValue( 0 )
					, _floatValue( 0.0 )
				{
					setKey( key );
					setValue( value );
				}

				FleetcomPair( const char* key, int value )
					: _type( NoType )
					, _key( NULL )
					, _strValue( NULL )
					, _intValue( 0 )
					, _floatValue( 0.0 )
				{
					setKey( key );
					setValue( value );
				}

				FleetcomPair( const char* key, double value )
					: _type( NoType )
					, _key( NULL )
					, _strValue( NULL )
					, _intValue( 0 )
					, _floatValue( 0.0 )
				{
					setKey( key );
					setValue( value );
				}

				~FleetcomPair()
				{
					delete [] _key;
					delete [] _strValue;
				}

				void setKey( const char* key )
				{
					delete _key;
					_key = NULL;

					if( strnlen( key, 256 ) > 0 )
					{
						int size = strnlen( key, 255 ) + 1;
						_key = new char[ size ];
						strncpy( _key, key, size );
					}
				}

				void setValue( const char* value )
				{
					delete _strValue;
					_strValue = NULL;
					_type = NoType;

					if( strnlen( value, 256 ) > 0 )
					{
						int size = strnlen( value, 255 ) + 1;
						_strValue = new char[ size ];
						strncpy( _strValue, value, size );
						_type = StringType;
					}
				}

				void setValue( int value )
				{
					delete _strValue;
					_strValue = NULL;

					_type = IntType;
					_intValue = value;
				}

				void setValue( double value )
				{
					delete _strValue;
					_strValue = NULL;

					_type = FloatType;
					_floatValue = value;
				}
				
				Type type() const { return _type; }

				const char* key() const { return _key; }

				int intValue() const { return _intValue; }

				double floatValue() const { return _floatValue; }

				const char* stringValue() const { return _strValue; }

				void clear()
				{
					delete _key;
					_key = NULL;

					delete _strValue;
					_strValue = NULL;

					_type = NoType;
				}

			private:
				Type _type;
				char* _key;
				char* _strValue;
				int _intValue;
				double _floatValue;
			};
		}
	}
}

#endif //_REC_ROBOTINO_API2_FLEETCOMPAIR_H_
