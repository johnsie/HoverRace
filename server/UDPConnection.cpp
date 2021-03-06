// GrokkSoft HoverRace SourceCode License v1.0, November 29, 2008
// 
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
// - Redistributions in source code must retain the accompanying copyright notice,
//   this list of conditions, and the following disclaimer. 
// - Redistributions in binary form must reproduce the accompanying copyright
//   notice, this list of conditions, and the following disclaimer in the
//   documentation and/or other materials provided with the distribution. 
// - Names of the copyright holders (Richard Langlois and Grokksoft inc.) must not
//   be used to endorse or promote products derived from this software without
//   prior written permission from the copyright holders. 
// - This software, or its derivates must not be used for commercial activities
//   without prior written permission from the copyright holders. 
// - If any files are modified, you must cause the modified files to carry
//   prominent notices stating that you changed the files and the date of any
//   change. 
// 
// Disclaimer: 
//   The author makes no representations about the suitability of this software for
//   any purpose.  It is provided "AS IS", WITHOUT WARRANTIES OR CONDITIONS OF ANY
//   KIND, either express or implied.
// 

/***
 * UDPConnection.h
 * Implementation of UDPConnection class, which abstracts away communication via
 * UDP.
 *
 * @author Ryan Curtin
 */
#include "UDPConnection.h"

using namespace boost::asio;
using namespace boost::asio::ip;

UDPConnection::UDPConnection() { /* nothing to do */

void UDPConnection::setEndpoint(udp::endpoint &endpoint)
{
	this->endpoint = endpoint;
}
