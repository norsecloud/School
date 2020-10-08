// -*-C++-*-
// Copyright (C) 1993 Latitude Communications, Inc.
// All rights reserved.
//
//
////////////////////////////////////////////////////////////////
/*
FILEHEADER+
****************************************************************
Filename:	cmsnetwk.h

Description:

  This file implements the OSD routines needed for communication between
  client and server processes. On the CM box, it uses LYNX messages and
  mailboxes. On Windows, it uses sockets.

Public Functions:

$Revision: 1.30 $

Date        Who                 What
----------  ------------------	-------------------------------
1/5/94      Wayne Fenton
$Log: cmsnetwk.h,v $
Revision 1.30  2004/03/11 01:04:31  dasingle
(GWSIM) Added #includes as per Jason Li.

Revision 1.29  2004/02/26 22:22:12  dasingle
(GWSIM) added includes for gateway builds.

Revision 1.28  2002/12/27 16:27:43  daves
(GWSIM) CR20013 GWSIM API should use cmsnetwork message functions.
Changed return type of GetRespMsg from exc to resp_t in new cmsnetwork
class.

Revision 1.27  2002/10/01 21:21:03  btoombs
Changed a 0xffff literal to ~0 to got rid of a compiler warning on the
gateway side.

Revision 1.26  2001/05/23 04:54:10  daves
4.3 to 5.0 merge.

Revision 1.25.4.1  2001/04/26 01:54:58  daves
Multiserver GWSIM support

Revision 1.25  2000/05/19 21:32:01  dqu

Add SendGWMsg function

Revision 1.24  2000/02/24 01:11:16  daves
Pass const char* to SetQName().

Revision 1.23  2000/02/23 02:00:20  raymond
SNA messages and functions

Revision 1.22  2000/01/21 17:49:23  daves
Added SeqQName and DelQueue for GWSIM_IMC.

Revision 1.21  1999/06/17 19:48:52  daves
(GWSIM) Use the Lynx routines if we're using GWSIM IMC.

Revision 1.20  1999/02/11 15:48:16  dave
Allow us to screen the messages we can delete.

Revision 1.19  1998/08/10 04:25:03  dave
Some changes for communications for ns and cs.

Revision 1.18  1998/08/06 04:07:41  dave
The new stuff for 98.2.

Revision 1.17  1998/03/05 02:38:59  kiran
The first checkin of MP98.1 stuff...

Revision 1.16  1996/07/04 20:47:20  stuart
Merge back the 3.0 sources.

Revision 1.15.2.1  1996/07/01 23:05:48  stuart
Add GetMailboxNumber()

Revision 1.15  1996/04/03 23:39:21  dave
Add the final build stuff before beta.

Revision 1.14  1996/02/06 16:58:10  reinaldo
Allow for client to specify the name of the Queue to receive messages.
Create a new SetUpForCommunications that accepts a name.

Revision 1.13  1996/01/03 00:39:25  dave
Added a new parameter to GetMsg -> the class of the msg expected.

Revision 1.12  1995/08/17 22:03:42  hahn
Macintosh has to handle asynchronous events, too.

 * Revision 1.11  1995/07/06  00:36:54  dave
 * Added a flush capability for clients to clean their queues.
 *
 * Revision 1.10  1995/02/08  02:43:44  dave
 * Create initialize functions for the xtable classes
 * MOdify Makefile to account for xlinitbin instead of xlinit
 * Modify xltest to display all the possible matches.
 * General display messages changed.
 *
 * Revision 1.9  1994/09/16  02:29:53  dave
 * Better error checking for cmsnetwk.cc  Also getting ready for Rel 1.1.
 *
 * Revision 1.8  1994/03/11  16:14:45  dave
 * Corrected the size of msg_code.
 *
 * Revision 1.7  1994/02/10  22:15:36  dave
 * Changes made to put the architecture dependent sections of the APIs into
 * cmsnetwk.
 *
 * Revision 1.6  1994/02/03  07:10:01  wayne
 * Added #includes, forward decls for class definition of Cimc_msg, fixed
 * prototype for HandleAsyncMsg
 *
 * Revision 1.5  1994/02/03  02:16:39  wayne
 * fixed some syntax errors on Windows
 *
 * Revision 1.4  1994/02/01  17:01:26  hahn
 * Changes to support testing over TCP/IP ports as well as with mailboxes.
 *
 * Revision 1.3  1994/01/29  01:25:17  dave
 * This is the newest cmsnetwk that deals with resp queues.  Also, there
 * are now definitions for what value error codes for each server class should
 * start with.
 *

****************************************************************
FILEHEADER-
*/

#ifndef CMSNETWK
#define CMSNETWK 1

#include "latstd.h"
#include "time.h"

class Cimc_msg;        // forward decls to avoid including cm_msg.h
class Cimc_msg_max;

// Because we are dealing with asynchronous requests and responses
// we need a place to store the information while the application
// is doing other things.

struct RespTable { //Organisation of ResponseTable
    int16 SequenceNumber;
    msg_class MsgClass;
    msg_code Msg_code;
    time_t TimeOut_Value;
    Cimc_msg *Msg_ptr;
};

#ifndef _GWSIM

/**************************************************************
                     Public Prototypes
**************************************************************/

exc SetUpForCommunication (void);
exc SetUpForCommunication (char * pName);

exc SetUpForSockCommunication (const char *host); // Setup for WS testing.

uInt16 SendMsg (Cimc_msg * Msg);
uInt16 SendGWMsg (Cimc_msg * Msg);

// The following is used in the VUI because one queue
// serves up to 8 "clients"
#if !defined(MSWINDOWS)
exc GetMsg (int16 SequenceNumber,  msg_code MsgCode,
	    time_t TimeOfTimeout, Cimc_msg *  Msg);
exc SendRemoteMsg (unit_t DestUnit,
		   Cimc_msg * pMsg,
		   Boolean fUseDefaultMBox = TRUE);

exc SnaSendRemoteMsg (unit_t DestUnit,
	              Cimc_msg * pMsg,
                      Boolean fUseDefaultMBox = TRUE);


exc GetRemoteMsg (unit_t SourceUnit,
		  msg_class ServerClass,
		  int16 SequenceNumber,
		  msg_code MsgCode,
		  time_t Timeout);
resp_t InitRemoteMsging (int16 nMaxConcurrentRequests,
			 Boolean fIsDBUnit);

uInt16 SendDBUnitMsg (Cimc_msg * Msg);
// Return the mailbox number (1-n) for the client mailbox used
// by these routines.  Note, this is NOT the whole mailbox ID.

uInt32 GetMailboxNumber(void);

#endif

resp_t GetRespMsg (msg_class ServerClass,
		   int16 SequenceNumber,
		   msg_code MsgCode,
		   Cimc_msg ** ppMsg,
		   unit_t Unit = NOUNITROUTING);


exc RegisterMsgClassHandler (uInt8 MsgClass,
			     exc (*Handler)  (Cimc_msg * ) );

void InitRespTable(int16 ConcurrentRequests);
void FlushRespTable(msg_class ClassToPurge,
		    int16 SequenceMask = ~0);
void CloseRespTable( );

Boolean AddOutGoingRequest(msg_class MsgClass,
			   int16 SequenceNumber,
			   msg_code Msg_code,
			   time_t TimeOutValue);


resp_t RegIncomingRespMsg(Cimc_msg * msg_ptr);

resp_t GetMsgFromRespTable (msg_class MsgClass,
			    int16 SequenceNumber,
			    msg_code Msg_code,
			    Cimc_msg * *msg_ptr,
			    uInt16 Location);


resp_t  CheckRespTable(msg_class MsgClass,
		       int16 SequenceNumber,
		       msg_code Msg_code,
		       time_t * pTimeOut,
		       Cimc_msg * *msg_ptr,
		       uInt16 * pLocation);


Cimc_msg_max * MallocMsg(void);

void FreeMsg(Cimc_msg * pMsg);


// We can get asynchronous message events from server.
// Deal with them specially.
#ifndef Lynx

uInt16 HandleAsyncMsg(void *pBuff);

#endif
#else

#include "cmmutex.h"
#include "cm_msg.h"
#include "cm_mbox.h"

#define CLIENT_NAME_QUEUE_LEN  50
#define MARGINOFSAFETY 10

class CMSNetwork {

public:

    Boolean fComInit;
    Boolean fRespInit;
    Boolean fUseClientName;
    char ClientQueueName[CLIENT_NAME_QUEUE_LEN];
    uInt32 nMaxConcurrentRequests;
    struct RespTable* pHeadQueue;
    Cimc_clientMB* clientMB;
    Cmutex mutex;
    int server_index;

    CMSNetwork(int index) {
	server_index = index;
	fComInit = FALSE;
	fRespInit = FALSE;
	fUseClientName = FALSE;
	memset(ClientQueueName, 0, CLIENT_NAME_QUEUE_LEN);
	nMaxConcurrentRequests = 0;
	pHeadQueue = 0;
	clientMB = 0;
    }

    // Set the queue name used for IMC routing.
    exc SetQName(const char* name);

    // Delete the queue used for IMC routing.
    exc DelQueue();

    void lock();
    void unlock();
    void initlock();

    exc SetUpForCommunication(char*);
    exc SetUpForSockCommunication(const char *host); // Setup for WS testing.

    uInt16 SendMsg(Cimc_msg * Msg);
    uInt16 SendGWMsg(Cimc_msg * Msg);

    exc GetMsg(int16 SequenceNumber, msg_code MsgCode,
	time_t TimeOfTimeout, Cimc_msg* Msg);

    exc GetMsg (msg_class ServerClass,
	int16 SequenceNumber,
	msg_code MsgCode,
	time_t Timeout);

    exc CheckForMsg(Cimc_msg* pMsg);

    uInt16 SendDBUnitMsg(Cimc_msg * Msg);
    // Return the mailbox number (1-n) for the client mailbox used
    // by these routines.  Note, this is NOT the whole mailbox ID.

    uInt32 GetMailboxNumber(void);

    Boolean IsMyMsgHere (msg_class ServerClass,
	msg_code MsgCode, int16 SequenceNumber);

    resp_t GetRespMsg(msg_class ServerClass, int16 SequenceNumber,
	msg_code MsgCode, Cimc_msg ** ppMsg,
	unit_t Unit = NOUNITROUTING);

    exc RegisterMsgClassHandler(uInt8 MsgClass, exc (*Handler)(Cimc_msg*, int));

    void InitRespTable(int16 ConcurrentRequests);
    void FlushRespTable(msg_class ClassToPurge, int16 SequenceMask = ~0);
    void CloseRespTable();

    Boolean AddOutGoingRequest(msg_class MsgClass,
	int16 SequenceNumber, msg_code Msg_code,
	time_t TimeOutValue);

    resp_t RegIncomingRespMsg(Cimc_msg* msg_ptr);

    resp_t GetMsgFromRespTable(msg_class MsgClass,
	int16 SequenceNumber,
	msg_code Msg_code,
	Cimc_msg * *msg_ptr,
	uInt16 Location);

    resp_t CheckRespTable(msg_class MsgClass,
	int16 SequenceNumber,
	msg_code Msg_code,
	time_t* pTimeOut,
	Cimc_msg * *msg_ptr,
	uInt16 * pLocation);

    Cimc_msg_max* MallocMsg(void);

    void FreeMsg(Cimc_msg* pMsg);

    uInt16 HandleAsyncMsg(void *pBuff);
};

extern CMSNetwork* cmsnet[];

#endif

#endif /* CMSNETWRK */
