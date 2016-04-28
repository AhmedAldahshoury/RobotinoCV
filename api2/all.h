//  Copyright (C) 2004-2008, Robotics Equipment Corporation GmbH

//Copyright (c) ...
//
//REC Robotics Equipment Corporation GmbH, Planegg, Germany. All rights reserved.
//Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//
//THIS SOFTWARE IS PROVIDED BY REC ROBOTICS EQUIPMENT CORPORATION GMBH �AS IS� AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL REC ROBOTICS EQUIPMENT CORPORATION GMBH
//BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
//GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//Copyright (c) ...
//
//REC Robotics Equipment Corporation GmbH, Planegg, Germany. Alle Rechte vorbehalten.
//Weiterverbreitung und Verwendung in nichtkompilierter oder kompilierter Form, mit oder ohne Ver�nderung, sind unter den folgenden Bedingungen zul�ssig:
//1) Weiterverbreitete nichtkompilierte Exemplare m�ssen das obige Copyright, diese Liste der Bedingungen und den folgenden Haftungsausschluss im Quelltext enthalten.
//2) Weiterverbreitete kompilierte Exemplare m�ssen das obige Copyright, diese Liste der Bedingungen und den folgenden Haftungsausschluss in der Dokumentation und/oder anderen Materialien, die mit dem Exemplar verbreitet werden, enthalten.
//
//DIESE SOFTWARE WIRD VON REC ROBOTICS EQUIPMENT CORPORATION GMBH OHNE JEGLICHE SPEZIELLE ODER IMPLIZIERTE GARANTIEN ZUR VERF�GUNG GESTELLT, DIE UNTER
//ANDEREM EINSCHLIESSEN: DIE IMPLIZIERTE GARANTIE DER VERWENDBARKEIT DER SOFTWARE F�R EINEN BESTIMMTEN ZWECK. AUF KEINEN FALL IST REC ROBOTICS EQUIPMENT CORPORATION GMBH
//F�R IRGENDWELCHE DIREKTEN, INDIREKTEN, ZUF�LLIGEN, SPEZIELLEN, BEISPIELHAFTEN ODER FOLGESCH�DEN (UNTER ANDEREM VERSCHAFFEN VON ERSATZG�TERN ODER -DIENSTLEISTUNGEN;
//EINSCHR�NKUNG DER NUTZUNGSF�HIGKEIT; VERLUST VON NUTZUNGSF�HIGKEIT; DATEN; PROFIT ODER GESCH�FTSUNTERBRECHUNG), WIE AUCH IMMER VERURSACHT UND UNTER WELCHER VERPFLICHTUNG
//AUCH IMMER, OB IN VERTRAG, STRIKTER VERPFLICHTUNG ODER UNERLAUBTER HANDLUNG (INKLUSIVE FAHRL�SSIGKEIT) VERANTWORTLICH, AUF WELCHEM WEG SIE AUCH IMMER DURCH DIE BENUTZUNG
//DIESER SOFTWARE ENTSTANDEN SIND, SOGAR, WENN SIE AUF DIE M�GLICHKEIT EINES SOLCHEN SCHADENS HINGEWIESEN WORDEN SIND.

#include "/RobotinoCV/api2/ComId.h"
#include "/RobotinoCV/api2/Com.h"
#include "/RobotinoCV/api2/defines.h"
#include "/RobotinoCV/api2/ComObject.h"
#include "/RobotinoCV/api2/Camera.h"
#include "/RobotinoCV/api2/CameraCapabilities.h"
#include "/RobotinoCV/api2/CameraFormat.h"
#include "/RobotinoCV/api2/CustomMessage.h"
#include "/RobotinoCV/api2/AnalogInput.h"
#include "/RobotinoCV/api2/AnalogInputArray.h"
#include "/RobotinoCV/api2/DigitalInput.h"
#include "/RobotinoCV/api2/DigitalInputArray.h"
#include "/RobotinoCV/api2/DigitalOutput.h"
#include "/RobotinoCV/api2/DigitalOutputArray.h"
#include "/RobotinoCV/api2/DistanceSensor.h"
#include "/RobotinoCV/api2/DistanceSensorArray.h"
#include "/RobotinoCV/api2/ElectricalGripper.h"
#include "/RobotinoCV/api2/Bumper.h"
#include "/RobotinoCV/api2/Motor.h"
#include "/RobotinoCV/api2/MotorArray.h"
#include "/RobotinoCV/api2/NorthStar.h"
#include "/RobotinoCV/api2/NorthStarReadings.h"
#include "/RobotinoCV/api2/OmniDrive.h"
#include "/RobotinoCV/api2/PowerManagement.h"
#include "/RobotinoCV/api2/Relay.h"
#include "/RobotinoCV/api2/RelayArray.h"
#include "/RobotinoCV/api2/ElectricalGripper.h"
#include "/RobotinoCV/api2/Odometry.h"
#include "/RobotinoCV/api2/PowerOutput.h"
#include "/RobotinoCV/api2/EncoderInput.h"
#include "/RobotinoCV/api2/RobotinoException.h"
#include "/RobotinoCV/api2/Grappler.h"
#include "/RobotinoCV/api2/GrapplerReadings.h"
#include "/RobotinoCV/api2/Kinect.h"
#include "/RobotinoCV/api2/LaserRangeFinder.h"
#include "/RobotinoCV/api2/LaserRangeFinderReadings.h"
#include "/RobotinoCV/api2/CompactBHA.h"
#include "/RobotinoCV/api2/Shutdown.h"
#include "/RobotinoCV/api2/Charger.h"
#include "/RobotinoCV/api2/PowerButton.h"
#include "/RobotinoCV/api2/Fleetcom.h"
#include "/RobotinoCV/api2/Gyroscope.h"
#include "/RobotinoCV/api2/utils.h"

/**  \mainpage rec::robotino::api2 C++ API documentation

The second version of the application programming interface (API2) for Robotino(r) from Festo Didactic permits full
access to Robotino's sensors and actors. Communication between the control program and Robotino
is handled via TCP, local sockets or shared memory. As its predecessor API2 is fully network transparent. It does not matter whether the
control program runs direcly on Robotino or on a remote system.

The API2 is available in binary form for <A HREF="http://wiki.openrobotino.org/index.php?title=Downloads">Windows and Linux</A> and <A HREF="http://svn.openrobotino.org/api2">source code</A>
via svn.

For instructions how to install the API2 and how to build C++ programs using API2 refer to the <A HREF="http://wiki.openrobotino.org/index.php?title=API2">Robotino Wiki</A>.
*/
