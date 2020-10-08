// -*-C++-*- (Emacs mode)

// Copyright (C) 1993 Latitude Communications, Inc.
// All rights reserved.

/* $Log $
 ******************************************************************
 *
 * cmsnetwk.cpp:  Conference Manager System dependant NetWork functions
 *
 * This file implements the operating system dependant network code. This has
 * to do with message passing and receiving. It's called from generic API
 * code, so it's implemented as a simple set of functions:
 *
 * SetUpForCommunications()
 * GetMsg()
 * SendMsg()
 * and one more for asynchronouse event handling
 *
 * These functions use whatever networking functionality is required on
 * the platform in question and include whatever header files are needed.
 * The header file snetwk.h shouldn't need and ifdef's since it's interface
 * shouldn't change.
 *
 * Revision History
 * -----------------
 * 12/28  Wfenton Created
 * $Log: cmsnetwk.cc,v $
 * Revision 1.113  2004/02/26 16:23:45  dasingle
 * Merged BToomb's web changes.
 *
 * Revision 1.112  2004/02/12 14:13:07  dasingle
 * (GWSIM) Log the size of the response table and any orphaned messages that are
 * found when adding a new message.
 *
 * Revision 1.111  2003/07/31 15:39:21  daves
 * Use ALTLOG instead of EXLOG for purge messages to prevent EXLOG floods.
 *
 * Revision 1.110  2002/05/21 20:25:18  daves
 * CR17300 GWSIM: Support 5.0 GWSIM backward compatibility.
 *
 * Revision 1.109  2002/01/11 23:36:39  schoy
 * CR15085 buff to save incoming message did not get initialized.
 *
 * Revision 1.108  2001/08/16 19:46:24  daves
 * Let SetUpForSockCommuncation use an IP address vs. hostname if provided.
 *
 * Revision 1.107  2001/05/23 04:54:10  daves
 * 4.3 to 5.0 merge.
 *
 * Revision 1.106.4.1  2001/04/26 01:54:58  daves
 * Multiserver GWSIM support
 *
 * Revision 1.106  2000/09/01 20:23:55  daves
 * (GWSIM) Include file changes.
 *
 * Revision 1.105  2000/08/04 18:36:04  daves
 * (GWSIM) Added Glenn's debugging code.
 *
 * Revision 1.104  2000/08/02 17:16:27  daves
 * Use delete vs. free.
 *
 * Revision 1.103  2000/06/21 21:42:50  daves
 * (GWSIM) Also bail from SendGWMsg() if no msg src.
 *
 * Revision 1.102  2000/06/21 21:23:07  daves
 * (GWSIM) If no msg source, bail from SendMsg().
 *
 * Revision 1.101  2000/05/19 21:32:00  dqu
 *
 * Add SendGWMsg function
 *
 * Revision 1.100  2000/05/18 21:42:38  daves
 * ALTLOG the purges for GWSIM.
 *
 * Revision 1.99  2000/05/18 19:30:50  daves
 * Only one ALTLOG for missing messages.
 *
 * Revision 1.98  2000/05/10 21:56:47  daves
 * More meaningful ALTLOGs for GWSIM.
 *
 * Revision 1.97  2000/04/21 20:30:25  daves
 * Use pointer for clientMB in GWSIM_IMC.
 *
 * Revision 1.96  2000/04/21 19:13:08  daves
 * Changed EXLOGs to ALTLOG for GWSIM.
 *
 * Revision 1.95  2000/04/03 22:52:42  daves
 * Eliminate more warnings from LynxOS 3.0 compiler.
 *
 * Revision 1.94  2000/02/23 02:00:19  raymond
 * SNA messages and functions
 *
 * Revision 1.93  2000/01/27 21:22:19  daves
 * Zero out clientMB after deleting it.
 *
 * Revision 1.92  2000/01/21 17:49:23  daves
 * Added SeqQName and DelQueue for GWSIM_IMC.
 *
 * Revision 1.91  1999/10/07 05:22:35  dave
 * Better checking when our table does not exist.
 *
 * Revision 1.90  1999/10/06 13:51:34  daves
 * Tweaked MSGTIMEOUT exception params.
 *
 * Revision 1.89  1999/07/09 01:33:10  daves
 * (GWSIM) Darn. Missed a curly brace.
 *
 * Revision 1.88  1999/07/09 01:02:17  daves
 * (GWSIM) Make sure mailbox name is set during reconnects.
 *
 * Revision 1.87  1999/06/17 19:15:50  daves
 * (GWSIM) Added GWSIM IMC routing support.
 *
 * Revision 1.86  1999/04/12 17:24:03  dave
 * If we get an event msg then we need to not use the msg ptr for it will have
 * been freed.
 *
 * Revision 1.85  1999/02/12 04:32:47  dave
 * Remove the warning.
 *
 * Revision 1.84  1999/02/11 15:55:46  dave
 * Fix the flush to be a little more aggressive.
 *
 * Revision 1.83  1999/02/11 15:48:18  dave
 * Allow us to screen the messages we can delete.
 *
 * Revision 1.82  1998/11/30 22:12:54  stuart
 * Eliminate warnings from LynxOS 3.0 compiler
 *
 * Revision 1.81  1998/11/13 08:47:10  dave
 * Check to see if your msg has arrived. Also, on init remote msgs,
 * do yourself and the NS if on a CS.
 *
 * Revision 1.80  1998/11/11 05:30:33  dave
 * We need to see if we get the remote msg early.
 *
 * Revision 1.79  1998/09/02 00:34:26  kiran
 * Changes to allow clients to compile..
 *
 * Revision 1.78  1998/08/10 04:25:02  dave
 * Some changes for communications for ns and cs.
 *
 * Revision 1.77  1998/08/06 05:50:08  dave
 * We cannot cache the mbox ids here.
 *
 * Revision 1.76  1998/08/06 04:07:40  dave
 * The new stuff for 98.2.
 *
 * Revision 1.75  1998/05/07 00:35:36  dave
 * Free the messages when not required.
 *
 * Revision 1.74  1997/08/29 01:31:29  kiran
 * Added pounddef for minwslogout and changed some names..
 *
 * Revision 1.73  1997/06/19 02:43:03  dave
 * If we are looking for one message and get another.... deal.
 *
 * Revision 1.72  1997/03/10 18:57:01  dave
 * Free memory if you are not going to use it.
 *
 * Revision 1.71  1997/02/03 17:57:37  stuart
 * Fix a warning and a formatting error.
 *
 * Revision 1.70  1996/12/10 21:44:01  stuart
 * Eliminate hard coding of CP message classes.
 *
 * Revision 1.69  1996/11/23 00:00:32  dave
 * Need to not chew so much memory.  3.0.2 fixes for release 3.0.
 *
 * Revision 1.68.2.1  1996/11/22 23:52:18  dave
 * Memory should not always be taken for granted.
 *
 * Revision 1.68  1996/10/03 01:44:59  stuart
 * Take out the startup info message.
 *
 * Revision 1.67  1996/09/26 23:46:22  dave
 * If we have signals stopping us from getting a message, and it is not
 * a timeout, keep waiting.
 *
 * Revision 1.66  1996/08/22 19:10:15  hahn
 * Changes for VC++ Macintosh build.
 *
 * Revision 1.65  1996/08/12 04:33:04  dave
 * Remove an error log statement when a multiunit system is not available.
 *
 * Revision 1.64  1996/07/23 01:42:12  stuart
 * Fix problem where SendMsg would try to return "exc" values instead of
 * "erc" values.
 *
 * Revision 1.63  1996/07/13 01:37:47  stuart
 * Add error definitions for cmsnetwk.
 *
 * Revision 1.62  1996/07/09 00:20:17  dave
 * In waiting for a remote message, wait the full time.
 *
 * Revision 1.61  1996/07/04 20:47:18  stuart
 * Merge back the 3.0 sources.
 *
 * Revision 1.59.2.4  1996/07/04 16:28:34  stuart
 * Improve error logging.
 *
 * Revision 1.59.2.3  1996/07/01 23:05:46  stuart
 * Add GetMailboxNumber()
 *
 * Revision 1.59.2.2  1996/06/07 22:24:16  stuart
 * Update for Release 3.0 (Big checkin)
 *
 * Revision 1.60  1996/05/10 07:31:05  dave
 * Better error loging and event log for db (user and group)
 *
 * Revision 1.59  1996/04/12 22:58:07  reinaldo
 * If you initialize the api classes, and then you decide that one (or
 * more) or your api classes should be able to deal with a multinoded
 * system. you only want to initialize the router once~!
 *
 * Revision 1.58  1996/04/09 01:11:34  dave
 * Make the windows version run, also show size in the error log.
 *
 * Revision 1.57  1996/04/03 23:39:19  dave
 * Add the final build stuff before beta.
 *
 * Revision 1.56  1996/02/26 19:25:29  reinaldo
 * Added a dummy SetUpForCommincations routine for clients.
 *
 * Revision 1.55  1996/02/12 21:13:11  wayne
 * got rid of include of stdafx.h
 *
 * Revision 1.54  1996/02/06 17:37:16  reinaldo
 * If setting up for communcation with a null name, use default Client
 * ID name.
 *
 * Revision 1.53  1996/02/06 16:58:09  reinaldo
 * Allow for client to specify the name of the Queue to receive messages.
 * Create a new SetUpForCommunications that accepts a name.
 *
 * Revision 1.52  1996/02/05 18:12:43  john
 * Extracted erc assignment from EXLOG in GetMsgFromRespTable
 *
 * Revision 1.51  1996/01/23 22:41:12  wayne
 * put in ismymsghere call in windows-specific getmsg to allow for nested
 * API sequences
 *
 * Revision 1.50  1996/01/03 00:39:23  dave
 * Added a new parameter to GetMsg -> the class of the msg expected.
 *
 * Revision 1.49  1995/11/16 22:45:39  dave
 * Hint string defs and extra logging in cmsnetwork.
 *
 * Revision 1.48  1995/11/02 22:57:27  dave
 * Preparing for the 2.0.a build.
 *
 * Revision 1.47  1995/10/26 15:24:56  dave
 * Can't have c++ style comments in files used by the db.
 *
 * Revision 1.46  1995/10/25 22:15:17  dave
 * First 2.0 build.
 *
 * Revision 1.45  1995/10/16 13:44:09  hahn
 *  Macintosh port related changes: don't return without disposing of a
 *  message buffer in cmsnetwk.cc, and don't log errors on any client,
 *  including Macs.
 *
 * Revision 1.44  1995/08/10 16:35:46  wayne
 * WINDOWS -> MSWINDOWS
 *
// Revision 1.43  1995/08/04  17:36:33  hahn
// We don't need wferc.h
//
// Revision 1.42  1995/08/02  00:11:58  hahn
// Changes for Macintosh compile.
//
// Revision 1.41  1995/07/06  00:36:30  dave
// Added a flush capability for the clients to clear their queues.
//
// Revision 1.40  1995/01/02  05:14:23  wayne
// Moved fComInit fRespInit out of Unix-Only. It's used elsewhere as well.
//
// Revision 1.39  1994/10/03  22:20:28  dave
// Better error logging.
//
// Revision 1.38  1994/09/16  17:00:24  dave
// Do not remalloc freddy!
//
// Revision 1.37  1994/09/16  04:11:40  dave
// Needed to be able to get the outstanding responses.
//
// Revision 1.36  1994/09/16  02:29:50  dave
// Better error checking for cmsnetwk.cc  Also getting ready for Rel 1.1.
//
// Revision 1.34  1994/09/02  00:16:05  dave
// Downgraded initialize log from a warn to an info.
//
// Revision 1.33  1994/08/30  02:25:37  dave
// Added app constants for the SIM App = also fixed the Millisecond conv.
// in cmsnetwk.cc.
//
// Revision 1.32  1994/07/21  23:40:00  hahn
// Clean up messages.
//
// Revision 1.31  1994/07/02  23:21:05  stuart
// Get rid of compiler warning.
//
// Revision 1.30  1994/06/28  21:40:19  stuart
// Use Cmutex.
//
// Revision 1.29  1994/06/09  17:22:44  hahn
// Add message buffering class for use by ws and test jig(s).
//
// Revision 1.28  1994/04/29  16:39:55  dave
// Changed evlog to include some of the other VUI log types.
//
// Revision 1.27  1994/04/19  06:21:33  dave
// Added the changes for the vui priority.
//
// Revision 1.25  1994/04/13  18:15:32  wayne
// Made some changes to the windows to code to help out with multiple reads
// for individual messages. Allows msgs to be broken up and re-assembled.
//
// Revision 1.24  1994/04/06  00:56:49  dave
// made some small changes to help debugging.
//
// Revision 1.22  1994/03/22  22:31:04  wayne
// changed std.h to be included on all platforms
//
// Revision 1.21  1994/03/18  04:02:46  dave
// Added another application to take care of a Glare case.  Also, fixed
// a shared memory problem on creating the links.
//
// Revision 1.20  1994/03/11  16:14:44  dave
// Corrected the size of msg_code.
//
// Revision 1.19  1994/03/08  22:56:03  stuart
// Fix problems that came out when I fixed the declarations for
// the mutexattr functions.
//
// Revision 1.18  1994/02/26  00:03:52  dave
// Made changes to support the VUI.
//
// Revision 1.17  1994/02/18  17:43:26  dave
// Added DTMF Bit masks, and sched parameters defaults and max and mins.
//
// Revision 1.16  1994/02/16  20:52:24  dave
// This is a boundary case of whether the timeout is > or >= the current
// time.
//
// Revision 1.14  1994/02/11  02:25:02  dave
// Made changes to this to allow multiple apis.
//
// Revision 1.13  1994/02/10  22:15:35  dave
// Changes made to put the architecture dependent sections of the APIs into
// cmsnetwk.
//
// Revision 1.12  1994/02/04  22:17:06  hahn
// Use netinet/in.h instead of bsd/in, and hide templates from paraset.
//
// Revision 1.11  1994/02/03  07:10:49  wayne
// Changed params to HandleAsyncMsg, got size of msg from msg itself
//
// Revision 1.10  1994/02/03  02:16:22  wayne
// fixed some syntax errors on Windows
//
// Revision 1.9  1994/02/03  01:52:29  wayne
// WINDOWS -> MSWINDOWS
//
// Revision 1.8  1994/02/01  17:01:25  hahn
// Changes to support testing over TCP/IP ports as well as with mailboxes.
//
// Revision 1.7  1994/01/29  01:25:16  dave
// This is the newest cmsnetwk that deals with resp queues.  Also, there
// are now definitions for what value error codes for each server class should
// start with.
//
// Revision 1.5  1994/01/24  22:19:11  wayne
// updated Windows versions of routines. Pulled out some generic code
// (RegisterMsgClassHandler() to top of file. Moved include of unistd.h
// down into this file from cm_msg.h.
//
// Revision 1.4  1994/01/24  18:21:00  dave
// Log revisions in cmsnetwk.cc.
//
 *
 ******************************************************************
 */

#define ENABLE_MP_CONVERSION		// Do byte swapping, etc. for this client

#if defined(_GWSIM)
#include <afx.h>
#endif

#include "latstd.h"
#include <std.h>
#include <time.h>
#include "cmbinary.h"
#include "cm_error.h"
#include "cmtelenm.h"
#include "cm_msg.h"
#include "cmconf.h"
#include "imcexc.h"
#include "cmsnetwk.h"

#if defined(_GWSIM)
#include "cmthread.h"
#include "cmmsgbuf.h"
#include "socknet.h"
#include "gwnet.h"

#else

#if !defined(MSWINDOWS)
#include <errno.h>
#include <unistd.h>		// needed for getpid()

#if defined(macintosh) && defined(__MWERKS__)  // 8/20/96 gah Mac Port: only check for __MWERKS__, not macintosh
#include <sys/socket.h>		// macintosh needs sys/ for GUSI network
#else
#include <socket.h>
#endif

#include <netinet/in.h>	// To get sockaddr_in, INADDR_ANY, etc. definitions
#include <arpa/inet.h>  // For inet_addr()
#include <netdb.h>		// To get gethostbyname()
#include <stdio.h>		// Not in MetroWerks std.h?

#if !defined( CLIENT) || defined(__MWERKS__)   // 8/20/96 gah Mac Port: only check for __MWERKS__, not macintosh
#include "cmmsgbuf.h"	// Only used on server to buffer messages.
#endif

#endif // #if !defined(MSWINDOWS)
#endif // #if defined(_GWSIM)

#if (defined(MSWINDOWS) || defined(macintosh))
/****************************************************************************
  Client: one global that needs to be accessed in order
  to send/receive messages
****************************************************************************/
#include "network.h"
extern CWFNetwork * theNetwork;

#ifdef _GWSIM
extern CWFNetwork * theNetwork_ms[CLIENT_MULTISERVER_ACCESS_MAX_SERVERS];
#endif

#endif // MSWINDOWS || macintosh

// Used only on unix or Gateway SIM platforms
#if defined(Lynx) || defined(_GWSIM)
#include "cm_mbox.h"
#include "cm_route.h"
#include "cmmutex.h"
#endif // LynxOS

exc CheckForMsg (Cimc_msg *  pMsg);

static  Boolean fComInit = FALSE;
static  Boolean fRespInit = FALSE;

#define CLIENT_NAME_QUEUE_LEN  50
static  Boolean fUseClientName = FALSE;
static  char    ClientNameQueue[CLIENT_NAME_QUEUE_LEN];

/****************************************************************************
                             GENERIC CODE (for all platforms)
****************************************************************************/
static uInt32    nMaxConcurrentRequests = 0;
static struct RespTable * pHeadQueue;
#define MARGINOFSAFTY 10     // How many extra requests can we have?!

struct MsgRouter {
    exc (*pMsgHandler) (Cimc_msg * );
} MsgRouterTable [IMC_CLASS_MAX] = {{NULL},
				    {NULL},
				    {NULL},
				    {NULL},
				    {NULL},
				    {NULL}};


// FORWARD DECLARATIONS ************************************************
exc GetMsg (msg_class ServerClass,
	    int16 SequenceNumber,
	    msg_code MsgCode,
	    time_t Timeout);


// END OF FORWARD DECLARATIONS *****************************************

/****************************************************************************
 *Function: RegisterMsgClassHandler
 *
 *Purpose: Because our APIs are suppose to be above the message routing
 * layer, then we need a way to register our APIs with the message
 * receiving functions.  This is that function!!!  When the other classes
 * get instanciated, they should register with this class and their messages
 * will be correctly handled, reguardless of who calls them!
 ****************************************************************************/
exc RegisterMsgClassHandler (uInt8 MsgClass,
			     exc (*Handler) (Cimc_msg *))
{
    exc ex;

    if (MsgClass < IMC_CLASS_MAX) {
	MsgRouterTable [MsgClass].pMsgHandler = Handler;
	ex = OK;
    } else
	ex = 1; // KKKK

    return (ex);


}
// Forward definitions!!!
static void lock();
static void unlock();
static void initlock();

/****************************************************************************
 *Function: InitRespTable
 *
 *Purpose: To build the ResponseTable and initializing it.
 ****************************************************************************/

void InitRespTable(int16 ConcurrentRequests)

{
    uInt32 i;

    if (fRespInit)
	return;

    if (ConcurrentRequests > (CM_MAX_ACCESS_PORTS * 2)) {
	EXLOG (SEV_MAJOR,EX_CONREQ,ConcurrentRequests,0,0,0);
	ConcurrentRequests = (CM_MAX_ACCESS_PORTS * 2);
    }

    nMaxConcurrentRequests = ConcurrentRequests;

    pHeadQueue = (struct RespTable *)
                malloc(sizeof(struct RespTable) *
                       (nMaxConcurrentRequests + MARGINOFSAFTY));

#ifdef _GWSIM
    ALTLOG(SEV_INFO, 0, nMaxConcurrentRequests, 0, 0, 0);
#endif

    // EXLOG (SEV_INFO,EX_QHEAD,(uInt32) pHeadQueue,0,0,0);

    if (pHeadQueue == NULL) {
	EXLOG (SEV_MAJOR,0,nMaxConcurrentRequests,0,0,0);
    }
    else {
        for (i=0; i<nMaxConcurrentRequests; i++) {
	    (pHeadQueue + i)->MsgClass = 0;
            (pHeadQueue + i)->SequenceNumber = 0;
            (pHeadQueue + i)->Msg_code = 0;
            (pHeadQueue + i)->TimeOut_Value = 0;
            (pHeadQueue + i)->Msg_ptr = NULL;
        }
    }
    initlock();

    fRespInit = TRUE;
}
/****************************************************************************
 *Function: FlushRespTable
 *
 *Purpose: This call will flush any and all outstanding messages waiting
 * for any given api.  Just provide it with the server class to purge
 * and it will do it's job.
 ****************************************************************************/

void FlushRespTable(msg_class ClassToPurge,
		    int16 SequenceMask)
{
    uInt32 i;

    if (!fRespInit)
	return;

    for (i=0; i<nMaxConcurrentRequests; i++) {
	if ((pHeadQueue + i)->MsgClass == ClassToPurge &&
	    (((SequenceMask == (int16) 0xffff) ||
	      ((pHeadQueue + i)->SequenceNumber & SequenceMask)) ||
		((pHeadQueue + i)->SequenceNumber == 0)) &&
	    (pHeadQueue + i)->Msg_code != 0) {
	    if ((pHeadQueue + i)->Msg_ptr != NULL) {
		ALTLOG (SEV_WARN,EX_PURGENONNULL,
		       (pHeadQueue + i)->Msg_ptr->seq,
		       (uInt32) (pHeadQueue + i)->Msg_ptr,
		       (pHeadQueue + i)->Msg_ptr->code,
		       (pHeadQueue + i)->Msg_ptr->session);
		FreeMsg ((pHeadQueue + i)->Msg_ptr);
	    }
	    ALTLOG (SEV_WARN,EX_PURGENULL,
		   ((pHeadQueue + i)->MsgClass + (i << 16)),
		   (pHeadQueue + i)->SequenceNumber,
		   (pHeadQueue + i)->Msg_code,
		   (pHeadQueue + i)->TimeOut_Value);

            // reset this entry to zero
	    (pHeadQueue + i)->SequenceNumber = 0;
	    (pHeadQueue + i)->MsgClass = 0;
	    (pHeadQueue + i)->Msg_ptr = NULL;

            (pHeadQueue + i)->Msg_code = 0;

	} // for any that meet the qualifications
    } // for all the possible messages in the queue



}

/****************************************************************************
 *Function: CloseRespTable
 *
 *Purpose: To close the response table and log any outstanding requests
 ****************************************************************************/

void CloseRespTable( )

{
    uInt32 i;

    if (!fRespInit)
	return;

    ALTLOG (SEV_INFO,EX_QHEAD,(uInt32) pHeadQueue,0,0,0);

    for (i=0; i<nMaxConcurrentRequests; i++) {
	if ((pHeadQueue + i)->Msg_code != 0) {
	    if ((pHeadQueue + i)->Msg_ptr != NULL) {
		ALTLOG (SEV_WARN,EX_PURGENONNULL,
		       (pHeadQueue + i)->Msg_ptr->seq,
		       (uInt32) (pHeadQueue + i)->Msg_ptr,
		       (pHeadQueue + i)->Msg_ptr->code,
		       (pHeadQueue + i)->Msg_ptr->session);
		FreeMsg ((pHeadQueue + i)->Msg_ptr);
	    }
	    ALTLOG (SEV_WARN,EX_PURGENULL,
		   ((pHeadQueue + i)->MsgClass + (i << 16)),
		   (pHeadQueue + i)->SequenceNumber,
		   (pHeadQueue + i)->Msg_code,
		   (pHeadQueue + i)->TimeOut_Value);

	}
    }
    fRespInit = FALSE;
    free (pHeadQueue);
    pHeadQueue = NULL;

}
/***************************************************************************
*Function: PutRespTable
*
*Purpose: To put the sequencenumber, message code and timeout value
          at the time of send.
****************************************************************************/
Boolean AddOutGoingRequest(msg_class MsgClass,
			   int16 SequenceNumber,
			   msg_code Msg_code,
			   time_t TimeOutValue)
{

    uInt32 i=0;
    Boolean fMadeEntry;

    if (!fRespInit)
	return FALSE;


    lock();

#ifdef _GWSIM
    time_t now = time(0);
#endif

    while ( ((pHeadQueue + i)->Msg_code) &&
	    i < nMaxConcurrentRequests)
    {
#ifdef _GWSIM
	if ((pHeadQueue+i)->TimeOut_Value < (now-10))
	{
	    ALTLOG(SEV_WARN, 0,
		    ((pHeadQueue + i)->MsgClass << 24) + i,
		    (pHeadQueue + i)->Msg_code,
		    (pHeadQueue + i)->SequenceNumber,
		    (pHeadQueue + i)->TimeOut_Value);
	}
#endif
	i++;
    }

    // DaveS 2/26/04 Merged BToombs change
    if (TimeOutValue < 1000000)      // It's a time interval, so add to the current time
	TimeOutValue += time(0);
    //

    if (i < nMaxConcurrentRequests) {
	(pHeadQueue + i)->MsgClass = MsgClass;
	(pHeadQueue + i)->SequenceNumber = SequenceNumber;
	(pHeadQueue + i)->Msg_code = Msg_code;
	(pHeadQueue + i)->TimeOut_Value = TimeOutValue;
	fMadeEntry = TRUE;
    } else {
#ifndef _GWSIM
	EXLOG (SEV_MAJOR,EX_QLOOP,i,(pHeadQueue + 0)->Msg_code,
		(pHeadQueue + 1)->Msg_code,
		(pHeadQueue + 2)->Msg_code);
#else
	ALTLOG (SEV_MAJOR,EX_QLOOP,i,MsgClass,Msg_code,TimeOutValue);
	for (int j=0;j<nMaxConcurrentRequests;j++) {
	    ALTLOG (SEV_MAJOR, 0,
		    ((pHeadQueue + j)->MsgClass << 24) + j,
		    (pHeadQueue + j)->Msg_code,
		    (pHeadQueue + j)->SequenceNumber,
		    (pHeadQueue + j)->TimeOut_Value);
	}
#endif
	fMadeEntry = FALSE;
    }
    unlock();

    return (fMadeEntry);
}
/***************************************************************************
*Function: RegIncomingRespMsg
*
*Purpose: To fill the table with message pointer.
***************************************************************************/
resp_t RegIncomingRespMsg(Cimc_msg * msg_ptr)
{

    uInt32 i;
    resp_t erc = ERC_NOTFOUND;

    if (!fRespInit)
	return ERC_SRVRNOTACTIVE;

    for (i=0; i<nMaxConcurrentRequests; i++) {
	if ( ((pHeadQueue + i)->SequenceNumber == int16(msg_ptr->seq)) &&
             ((pHeadQueue + i)->Msg_code == msg_ptr->code) &&
	     (pHeadQueue + i)->MsgClass == msg_ptr->MsgClass) {
		erc = ERC_OK;
 		break;
	}
    }

    if (erc == ERC_OK) {
	if ((pHeadQueue + i)->Msg_ptr != NULL) {
#ifndef _GWSIM
	    EXLOG (SEV_MINOR,EX_NONNULL,
		   (pHeadQueue + i)->Msg_ptr->MsgClass,
		   (uInt32) (pHeadQueue + i)->Msg_ptr,
		   (pHeadQueue + i)->Msg_ptr->code,
		   (pHeadQueue + i)->Msg_ptr->session);
	    EXLOG (SEV_WARN,EX_NONNULL2,i,
		   msg_ptr->code,
		   msg_ptr->session,
		   msg_ptr->seq);
#else
	    ALTLOG (SEV_MINOR,EX_NONNULL,
		   (pHeadQueue + i)->Msg_ptr->MsgClass,
		   (uInt32) (pHeadQueue + i)->Msg_ptr,
		   (pHeadQueue + i)->Msg_ptr->code,
		   (pHeadQueue + i)->Msg_ptr->session);
	    ALTLOG (SEV_WARN,EX_NONNULL2,i,
		   msg_ptr->code,
		   msg_ptr->session,
		   msg_ptr->seq);
#endif
	    free ((pHeadQueue + i)->Msg_ptr); // don't loose memory!
	}
	(pHeadQueue + i)->Msg_ptr = msg_ptr;
    }
    return(erc);
}
/*****************************************************************************
*Function: GetRespTable
*
*Purpose: To get the response message or timeout information.
****************************************************************************/
Boolean IsMyMsgHere (msg_class ServerClass,
		     msg_code MsgCode,
		     int16 SequenceNumber)
{
    Boolean fFoundMsg = FALSE;
    uInt32 i;

    if (!fRespInit)
	return FALSE;

#if defined(_GWSIM)
	if (!pHeadQueue)
		return FALSE;
#endif

    for (i=0; i<nMaxConcurrentRequests; i++) {
	if ( ((pHeadQueue + i)->SequenceNumber == SequenceNumber) &&
             ((pHeadQueue + i)->Msg_code == MsgCode) &&
	     ((pHeadQueue + i)->MsgClass == ServerClass) &&
	     (pHeadQueue + i)->Msg_ptr != NULL) {
		fFoundMsg = TRUE;
 		break;
	}
    }
    return (fFoundMsg);

}
/*****************************************************************************
*Function: GetMsgFromRespTable
*
*Purpose: To get the response message or timeout information.
******************************************************************************/
resp_t GetMsgFromRespTable (msg_class MsgClass,
			    int16 SequenceNumber,
			    msg_code Msg_code,
			    Cimc_msg * *msg_ptr,
			    uInt16 Location)
{
    resp_t erc = ERC_OK;
    time_t current_time;

    if (!fRespInit)
	return ERC_SRVRNOTACTIVE;


    if (Location < nMaxConcurrentRequests) {
	if ( ((pHeadQueue + Location)->SequenceNumber == SequenceNumber) &&
             ((pHeadQueue + Location)->Msg_code == Msg_code) &&
	     (pHeadQueue + Location)->MsgClass == MsgClass) {
	    // Yes we are here!!!!
	    if ((pHeadQueue + Location)->Msg_ptr != NULL) {
		// We have found our message!!!
		*msg_ptr = (pHeadQueue + Location)->Msg_ptr;
		(pHeadQueue + Location)->SequenceNumber = 0;
		(pHeadQueue + Location)->MsgClass = 0;
		(pHeadQueue + Location)->Msg_ptr = NULL;

		// MUST BE SET LAST SO WE DO NOT NEED A LOCK HERE!!!!
		(pHeadQueue + Location)->Msg_code = 0;
	    } else {
		// The message is not here yet!!!
		// Check for a timeout!
		time(&current_time);
		if (current_time >= (pHeadQueue + Location)->TimeOut_Value) {

		    // The Msg Pointer = NULL, so we timed out!!!
		    erc = ERC_TIMEOUT;
		    (pHeadQueue + Location)->SequenceNumber = 0;
		    (pHeadQueue + Location)->MsgClass = 0;
		    (pHeadQueue + Location)->Msg_ptr = NULL;
		    // MUST BE SET LAST SO WE DO NOT NEED A LOCK HERE!!!!
		    (pHeadQueue + Location)->Msg_code = 0;
		} else {
		    // No Timeout yet, but no msg....
		    erc = ERC_NOMSG;
		    // This should never happen!!!
		    // ACTUALLY, this can happen when we are trying
		    // to clean up the queue if we try to send a message
		    // to another unit and it is unavailable.
#if 0
		    EXLOG (SEV_WARN,EX_MISSINGMSG,
			   MsgClass,
			   SequenceNumber,
			   Msg_code,0);
#endif

		    (pHeadQueue + Location)->SequenceNumber = 0;
		    (pHeadQueue + Location)->MsgClass = 0;
		    (pHeadQueue + Location)->Msg_ptr = NULL;

		    // MUST BE SET LAST SO WE DO NOT NEED A LOCK HERE!!!!
		    (pHeadQueue + Location)->Msg_code = 0;

		}

	    }
	} else {
	    // the location is not correct!!! Or the message is gone
	    erc = ERC_INTERNALERROR;
#ifndef _GWSIM
	    EXLOG (SEV_MINOR,EX_INTERR2,erc,Location,nMaxConcurrentRequests,0);
	    EXLOG (SEV_INFO,0,
		   MsgClass,
		   SequenceNumber,
		   Msg_code,0);

	    EXLOG (SEV_INFO,0,
		   (pHeadQueue + Location)->MsgClass,
		   (pHeadQueue + Location)->SequenceNumber,
		   (pHeadQueue + Location)->Msg_code,0);
#else
	    ALTLOG (SEV_MINOR,EX_INTERR2,erc,Location,nMaxConcurrentRequests,0);
	    ALTLOG (SEV_INFO,0,
		   MsgClass,
		   SequenceNumber,
		   Msg_code,0);

	    ALTLOG (SEV_INFO,0,
		   (pHeadQueue + Location)->MsgClass,
		   (pHeadQueue + Location)->SequenceNumber,
		   (pHeadQueue + Location)->Msg_code,0);
#endif

	}

    } else {
	// WE are in a real bad situation!!!!
	erc = ERC_INTERNALERROR;
#ifndef _GWSIM
	EXLOG (SEV_MINOR,EX_INTERR2,erc,Location,nMaxConcurrentRequests,0);
#else
	ALTLOG (SEV_MINOR,EX_INTERR2,erc,Location,nMaxConcurrentRequests,0);
#endif
    }

    return (erc);

}

/*****************************************************************************
*Function: CheckRespTable
*
*Purpose: To get the response message or timeout information.
******************************************************************************/
resp_t CheckRespTable(msg_class MsgClass,
		      int16 SequenceNumber,
		      msg_code Msg_code,
		      time_t * pTimeOut,
		      Cimc_msg * *msg_ptr,
		      uInt16 * pLocation)
{

    uInt32 i;
    resp_t erc = ERC_NOTFOUND;
    time_t current_time;

    if (!fRespInit)
	return ERC_SRVRNOTACTIVE;


    for (i=0; i<nMaxConcurrentRequests; i++) {
	if ( ((pHeadQueue + i)->SequenceNumber == SequenceNumber) &&
             ((pHeadQueue + i)->Msg_code == Msg_code) &&
	     ((pHeadQueue + i)->MsgClass == MsgClass)) {
  		erc = ERC_OK;
		break;
	}
    }

    if (erc == ERC_OK) {
	// We have found the location for the message!
	if ((pHeadQueue + i)->Msg_ptr != NULL) {
	    // We have found our message and it is here!
	    *msg_ptr = (pHeadQueue + i)->Msg_ptr;
	    (pHeadQueue + i)->SequenceNumber = 0;
	    (pHeadQueue + i)->MsgClass = 0;

	    (pHeadQueue + i)->Msg_ptr = NULL;

	    // MUST BE SET LAST SO WE DO NOT NEED A LOCK HERE!!!!
	    (pHeadQueue + i)->Msg_code = 0;
	} else {
	    // The message is not here yet!!!
	    // Check for a timeout!
	    *msg_ptr = NULL;
	    *pTimeOut = (pHeadQueue + i)->TimeOut_Value;
	    *pLocation = i;

	    time(&current_time);
	    if (current_time > (pHeadQueue + i)->TimeOut_Value) {
		// Check for timeout
		erc = ERC_TIMEOUT;
	    } else {
		erc = ERC_NOMSG;
	    }
	} // end of having an empty table!
    } // end of finding the entry in the table
    else {
#ifndef _GWSIM
	EXLOG (SEV_WARN,EX_MISSINGMSG2,pHeadQueue[0].Msg_code,
	       pHeadQueue[0].SequenceNumber,
	       SequenceNumber,Msg_code);
#else
	ALTLOG (SEV_WARN, EX_MISSINGMSG2, MsgClass, Msg_code, SequenceNumber, 0);
#endif
    }

    return(erc);
}


/************************************************************************
 * Function: GetRespMsg
 *
 * Description: Try and place all the weird cmsnetwrk message calls in
 *  one location to isolate any possible bug/fixes to one spot
 *
 ************************************************************************/
resp_t GetRespMsg (msg_class ServerClass,
		   int16 SequenceNumber,
		   msg_code MsgCode,
		   Cimc_msg ** ppMsg,
		   unit_t Unit)
{

    resp_t erc;
    time_t     Timeout;
    uInt16 Location;

    erc = CheckRespTable(ServerClass,
			 SequenceNumber,
			 MsgCode,
			 &Timeout,
			 ppMsg,
			 &Location);

    // if there is no response yet - wait for msg
    if (erc == ERC_NOMSG) {
	if (Unit ==  NOUNITROUTING) {
	    (void) GetMsg (ServerClass,
			   SequenceNumber,
			   MsgCode,
			   Timeout);
	} else {
#ifdef MSWINDOWS
	    return(GetMsg (ServerClass,
			   SequenceNumber,
			   MsgCode,
			   Timeout));
#else
	    (void) GetRemoteMsg (Unit,
				 ServerClass,
				 SequenceNumber,
				 MsgCode,
				 Timeout);
#endif
	}
    }
    // fill out response from Msg
    if (erc && erc != ERC_NOTFOUND)
	erc = GetMsgFromRespTable (ServerClass,
				   SequenceNumber,
				   MsgCode,
				   ppMsg,
				   Location);

    return (erc);
}



/****************************************************************************
                             LYNX-SPECIFIC VERSIONS
****************************************************************************/
#if defined(Lynx)
Cimc_clientMB clientMB;
#elif defined(_GWSIM)
Cimc_clientMB* clientMB;
#endif

#if defined(Lynx) || defined(_GWSIM)

#define QNAME_CLIENT  "CLIENT"

uInt32
GetMailboxNumber()
{
#if !defined(_GWSIM)
    return MBOX_BASE(clientMB.getMbId());
#else
    return MBOX_BASE(clientMB ? clientMB->getMbId() : 0);
#endif
}

int	sockFd = 0;	// Set if using direct connection during WS testing.

static Cmutex mutex;

static void lock()
{
    if (!mutex.lock())
#ifndef _GWSIM
	EXLOG(SEV_WARN, 0, errno, 0, 0, 0);
#else
	ALTLOG(SEV_WARN, 0, errno, 0, 0, 0);
#endif
}

static void unlock()
{
    if (!mutex.unlock())
#ifndef _GWSIM
	EXLOG(SEV_WARN, 0, errno, 0, 0, 0);
#else
	ALTLOG(SEV_WARN, 0, errno, 0, 0, 0);
#endif
}

static void initlock()
{
    if (!mutex.initialize())
#ifndef _GWSIM
	EXLOG(SEV_WARN, 0, errno, 0, 0, 0);
#else
	ALTLOG(SEV_WARN, 0, errno, 0, 0, 0);
#endif
}


#ifdef _GWSIM
exc SetQName(const char* name) {
    if (strlen(name) > CLIENT_NAME_QUEUE_LEN-1)
	return -1;

    fUseClientName = TRUE;
    strcpy(ClientNameQueue, name);
    return 0;
}

exc DelQueue() {
    if (clientMB) {
	delete_mbox(clientMB);
	clientMB = 0;
    }
    return 0;
}
#endif


/****************************************************************************
 * Function: SetUpForCommunication
 *
 * Purpose: This version of SetUpForCommunication(pName) connects to a server
 *	using message queues and creates a message queue with the
 * specified name.
 ****************************************************************************/
exc SetUpForCommunication (char * pName)
{
    if (pName == NULL) {
	fUseClientName = FALSE;
    } else {
	fUseClientName = TRUE;
	memset (ClientNameQueue, '\0', CLIENT_NAME_QUEUE_LEN);
	memcpy (ClientNameQueue, pName, CLIENT_NAME_QUEUE_LEN);
    }
    return SetUpForCommunication ( );
}


/****************************************************************************
 * Function: SetUpForCommunication
 *
 * Purpose: This version of SetUpForCommunication() connects to a server
 *	using message queues.
 ****************************************************************************/
exc SetUpForCommunication (void )   // QUEST: PASS IN QNAME (char *)
{
    exc ex = OK;
    char ClientQueue [CLIENT_NAME_QUEUE_LEN];
    int pid;

#if defined(_GWSIM)

    //
    // If we haven't created our initial mailbox, or if we've lost our connection,
    // or if our mailbox is no longer valid, get a new one.
    //

    if (!clientMB || !theNetwork_ms[server_index]->IsConnected() ||
        imc_rte.checkMbId(clientMB->getMbId())) {
      if (clientMB) {
        ex = imc_rte.checkMbId(clientMB->getMbId());
	delete_mbox(clientMB);
      }
      clientMB = alloc_mbox();

      //
      // If we've registered once, we won't get down to the registration again, so
      // we need to do it here.
      //

      if (fComInit) {
        if (fUseClientName) {
          fUseClientName = FALSE;
          memcpy (ClientQueue, ClientNameQueue, CLIENT_NAME_QUEUE_LEN);
        } else {
          pid = getpid();
          strcpy (ClientQueue, QNAME_CLIENT);
          cm_itoa (&ClientQueue [strlen (ClientQueue)], pid);
        }
        ex = clientMB->registerName(ClientQueue);
      }
    }
#endif

    if (!fComInit) {
	ex = imc_rte.initialize(false);
	if (ex != OK) {
#ifndef _GWSIM
	    EXLOG (SEV_MAJOR, EX_RTEINIT,ex,0,0,0);
#else
	    ALTLOG (SEV_MAJOR, EX_RTEINIT,ex,0,0,0);
#endif
	}

	if (!ex) {
	    if (fUseClientName) {
		fUseClientName = FALSE;
		memcpy (ClientQueue, ClientNameQueue, CLIENT_NAME_QUEUE_LEN);

	    } else {
		pid = getpid();
		strcpy (ClientQueue, QNAME_CLIENT);
		cm_itoa (&ClientQueue [strlen (ClientQueue)], pid);
	    }

#if !defined(_GWSIM)
	    ex = clientMB.registerName(ClientQueue);
#else
      if (clientMB)
        ex = clientMB->registerName(ClientQueue);
      else
        ex = -1;
#endif
	    if (ex == OK) {
		fComInit = TRUE;
	    }
	}
    }
    return (ex);



}

/****************************************************************************
 * Function: SetUpForSockCommunication ( name )
 *
 * Purpose: This version of SetUpForCommunication() connects to a server
 *	using an IP port (like the Workstation does).
 *	It is used as part of the Workstation Server test jig.
 *
 ****************************************************************************/

exc SetUpForSockCommunication ( const char * name )
{
    struct hostent	*pHostEntry;	// Server host information.

    if (fComInit) {
	return (OK);
    }

    // Initialize the server host Internet address:
    struct sockaddr_in	hostAddr;	// Server host address.
    bzero((char *)&hostAddr, sizeof( hostAddr));
    hostAddr.sin_family      = AF_INET;
    hostAddr.sin_port        = htons(CM_IP_SERVICE_PORT); // Port:network order

    // See it was in numeric format already...

    hostAddr.sin_addr.s_addr = inet_addr((char*)name);
    if ((long)(hostAddr.sin_addr.s_addr) < 0)
    {
	// Set the host address from the host database
	if (! (pHostEntry = gethostbyname((char*)name)))
	{
	    // If we can't get the host, give up
#ifndef _GWSIM
	    EXLOG( SEV_MAJOR, EX_GETHOST, errno, 0, 0, 0);
#else
	    ALTLOG( SEV_MAJOR, EX_GETHOST, errno, 0, 0, 0);
#endif
	    return 1;
	}
	memcpy((char *) &hostAddr.sin_addr.s_addr,
		pHostEntry->h_addr,
		pHostEntry->h_length);
    }

    // Create the socket to connect on:
    const int	IPprotocol = 0;
    if(0>(sockFd = socket(AF_INET, SOCK_STREAM, IPprotocol))) {
#ifndef _GWSIM
	EXLOG( SEV_MAJOR, EX_SOCKFAIL, errno, 0, 0, 0);
#else
	ALTLOG( SEV_MAJOR, EX_SOCKFAIL, errno, 0, 0, 0);
#endif
	return 1;
    }

    // Now connect on the socket:
    if (0 > connect( sockFd, (struct sockaddr *) &hostAddr, sizeof(hostAddr))) {
#ifndef _GWSIM
	EXLOG( SEV_MAJOR, EX_CONNFAIL, sockFd, errno, 0, 0);
#else
	ALTLOG( SEV_MAJOR, EX_CONNFAIL, sockFd, errno, 0, 0);
#endif
	return errno;
    }

    fComInit = TRUE;
    // All clear.
    return OK;
}

/****************************************************************************
 *Function: SendMsg
 *
 *Purpose:
 ****************************************************************************/
uInt16 SendMsg (Cimc_msg * pMsg)
{
    exc ex;

    // Use socket to send the message if testing WS.
    if (sockFd) {
	const int   noFlags = 0;
#if !defined(_GWSIM)
	if (pMsg->msgSize > send(sockFd, (void *)pMsg, pMsg->msgSize, noFlags)){
#else
  if (pMsg->msgSize > send(sockFd, (const char*)pMsg, pMsg->msgSize, noFlags)){
#endif
#ifndef _GWSIM
	    EXLOG (SEV_WARN, 0,0,0,0,0);
#else
	    ALTLOG (SEV_WARN, 0,0,0,0,0);
#endif
	    return (1);
	}
	return OK;
    }
    ex = imc_rte.queryServer(pMsg->MsgClass, pMsg->dst);
    if (ex != OK) {
#ifndef _GWSIM
	EXLOG (SEV_WARN, EX_QUERYSERV2,ex,pMsg->MsgClass,0,0);
#else
	ALTLOG (SEV_WARN, EX_QUERYSERV2,ex,pMsg->MsgClass,0,0);
#endif
	return (ERC_NOTFOUND);
    }
#if !defined(_GWSIM)
    pMsg->src = clientMB.getMbId();
    ex = clientMB.request((*pMsg));
#else
    if (clientMB) {
	pMsg->src = clientMB->getMbId();
	if (pMsg->src == 0)
	    return(ERC_INTERNALERROR); // Server wouldn't be able to respond
	ex = clientMB->request((*pMsg));
    }
    else
      ex = -1;
#endif

    if (ex != OK) {
#ifndef _GWSIM
	EXLOG (SEV_WARN, EX_REQFAIL,ex,0,0,0);
#else
	ALTLOG (SEV_WARN, EX_REQFAIL,ex,0,0,0);
#endif
	return (ERC_BUSY);
    }

    return ERC_OK;
}




/****************************************************************************
 *Function: SendGWMsg
 *
 *Purpose: Send a message to any mailbox, including a remote gateway,
 *         without doing a server lookup.
 ****************************************************************************/

uInt16 SendGWMsg (Cimc_msg * pMsg)
{
    exc ex;

    // Use socket to send the message if testing WS.
    if (sockFd) {
	const int   noFlags = 0;
#if !defined(_GWSIM)
	if (pMsg->msgSize > send(sockFd, (void *)pMsg, pMsg->msgSize, noFlags)){
#else
	if (pMsg->msgSize > send(sockFd, (const char*)pMsg, pMsg->msgSize, noFlags)){
#endif

#ifndef _GWSIM
	    EXLOG (SEV_WARN, 0,0,0,0,0);
#else
	    ALTLOG (SEV_WARN, 0,0,0,0,0);
#endif
	    return (1);
	}
	return OK;
    }

#if !defined(_GWSIM)
    pMsg->src = clientMB.getMbId();
    ex = clientMB.request((*pMsg));
#else
    if (clientMB) {
	pMsg->src = clientMB->getMbId();
	if (pMsg->src == 0)
	    return(ERC_INTERNALERROR); // Server wouldn't be able to respond
	ex = clientMB->send((*pMsg));
    }
    else
	ex = -1;
#endif

    if (ex != OK) {
#ifndef _GWSIM
	EXLOG (SEV_WARN, EX_REQFAIL,ex,0,0,0);
#else
	ALTLOG (SEV_WARN, EX_REQFAIL,ex,0,0,0);
#endif
	return (ERC_BUSY);
    }

    return ERC_OK;
}




/****************************************************************************
 *Function: SendDBUnitMsg
 *
 *Purpose: the only difference is that this can ONLY send messages to
 *  the db unit.!!!!..
 ****************************************************************************/
uInt16 SendDBUnitMsg (Cimc_msg * pMsg)
{
    exc ex;

    // Use socket to send the message if testing WS.
    if (sockFd) {
	const int   noFlags = 0;
#if !defined(_GWSIM)
	if (pMsg->msgSize > send(sockFd, (void *)pMsg, pMsg->msgSize, noFlags)){
#else
	if (pMsg->msgSize > send(sockFd, (const char*)pMsg, pMsg->msgSize, noFlags)){
#endif
#ifndef _GWSIM
	    EXLOG (SEV_WARN, 0, 0,0,0,0);
#else
	    ALTLOG (SEV_WARN, 0, 0,0,0,0);
#endif
	    return 1;
	}
	return OK;
    }
    ex = imc_rte.queryServer(pMsg->MsgClass, 0,pMsg->dst);
    if (ex != OK) {
#ifndef _GWSIM
	EXLOG (SEV_WARN, EX_QUERYSERV2,ex,pMsg->MsgClass,0,0);
#else
	ALTLOG (SEV_WARN, EX_QUERYSERV2,ex,pMsg->MsgClass,0,0);
#endif
	return (ERC_NOTFOUND);
    }
#if !defined(_GWSIM)
    pMsg->src = clientMB.getMbId();
    ex = clientMB.request((*pMsg));
#else
    if (clientMB) {
      pMsg->src = clientMB->getMbId();
      ex = clientMB->request((*pMsg));
    }
    else
      ex = -1;
#endif
    if (ex != OK) {
#ifndef _GWSIM
	EXLOG (SEV_WARN, EX_REQFAIL,ex,0,0,0);
#else
	ALTLOG (SEV_WARN, EX_REQFAIL,ex,0,0,0);
#endif
	return (ERC_BUSY);
    }

    return ERC_OK;

}
/****************************************************************************
 *Function: CheckForMsg
 *
 *Purpose: The purpose of this is to get any new message off the message
 *  queue and have it fill forwarded to the API that needs it.  If the
 *  calling routine passes it a 0 msgcode and a 0 sequence number, then
 *  any new message will trigger a return.  The pMsg will always be filled
 *  out with the header of the message (or a Cimc_msg).  This way, the
 *  calling routine can determine what to do now, if a 0 msgcode and a 0
 *  sequence number was provided.
 *
 ****************************************************************************/
exc CheckForMsg (Cimc_msg *  pMsg)

{
    exc ex = OK;
    Boolean fDone = FALSE;

    Cimc_msg_max * pMaxMsg;


    while (!fDone) {
	pMaxMsg = MallocMsg ();
	if (pMaxMsg == NULL) {
#ifndef _GWSIM
	    EXLOG (SEV_MAJOR,EX_MALLOCFAIL,errno,0,0,0);
#else
	    ALTLOG (SEV_MAJOR,EX_MALLOCFAIL,errno,0,0,0);
#endif

	    return (ERC_OUTOFMEMORY);   // ERROR ERROR - RETURN
	}

#if !defined(_GWSIM)
	ex = clientMB.receiveResponse((*pMaxMsg),
				      IMC_MAX_BODYSIZE + sizeof (Cimc_msg),
				      0); // do not wait - return
#else
  if (clientMB)
    ex = clientMB->receiveResponse((*pMaxMsg),
              IMC_MAX_BODYSIZE + sizeof (Cimc_msg),
              0); // do not wait - return
  else
    ex = -1;
#endif

	if (ex != OK) {
	    fDone = TRUE;
	}
	else {
	    // we have a message - deal (as WF would say!)
	    if (pMaxMsg->MsgClass < IMC_CLASS_MAX &&
		MsgRouterTable [pMaxMsg->MsgClass].pMsgHandler != NULL) {
		ex = MsgRouterTable [pMaxMsg->MsgClass].pMsgHandler (pMaxMsg);
		*pMsg = *pMaxMsg;
	    } else {
#ifndef _GWSIM
		EXLOG (SEV_MAJOR,
		       EX_INVMSGCLS,
		       pMaxMsg->MsgClass,
		       0,0,0);
#else
		ALTLOG (SEV_MAJOR,
		       EX_INVMSGCLS,
		       pMaxMsg->MsgClass,
		       0,0,0);
#endif
	    }
	    fDone = TRUE;  // this keeps this routine from being EmptyQueue

	} /* end dealing with a message */
    } // while we still have messages on the queue

    return (ex);
}

/****************************************************************************
 *Function: GetMsg
 *
 *Purpose: The purpose of this is to get any new message off the message
 *  queue and have it fill forwarded to the API that needs it.  If the
 *  calling routine passes it a 0 msgcode and a 0 sequence number, then
 *  any new message will trigger a return.  The pMsg will always be filled
 *  out with the header of the message (or a Cimc_msg).  This way, the
 *  calling routine can determine what to do now, if a 0 msgcode and a 0
 *  sequence number was provided.
 *
 ****************************************************************************/
exc GetMsg (int16 SequenceNumber,
	    msg_code MsgCode,
	    time_t Timeout,
	    Cimc_msg *  pMsg)

{
    exc ex = OK;
    Boolean fNotFound = TRUE;
    time_t Now;
    int32 MsgReceiveTimeOut;
    Cimc_msg_max * pMaxMsg;

    if (Timeout != 0) {
	//
	time(&Now);
	if (Now < Timeout) {
	    // we have not yet timed out
	    MsgReceiveTimeOut = (Timeout - Now) * 1000; // Milliseconds
	} else
	    MsgReceiveTimeOut = 0;  // get whatever is there!
    } else
	// wait forever!!!
	MsgReceiveTimeOut = -1;


    while (fNotFound && ex == OK) {
	pMaxMsg = MallocMsg ();
	if (pMaxMsg == NULL) {
#ifndef _GWSIM
	    EXLOG (SEV_MAJOR,EX_MALLOCFAIL,MsgCode,
		   SequenceNumber,0,0);
#else
	    ALTLOG (SEV_MAJOR,EX_MALLOCFAIL,MsgCode,
		   SequenceNumber,0,0);
#endif
	    return (ERC_OUTOFMEMORY);   // ERROR ERROR - RETURN
	}
	if (! sockFd) {
#if !defined(_GWSIM)
	    ex = clientMB.receive((*pMaxMsg),
				  IMC_MAX_BODYSIZE + sizeof (Cimc_msg),
				  MsgReceiveTimeOut);
#else
      if (clientMB)
         ex = clientMB->receive((*pMaxMsg),
            IMC_MAX_BODYSIZE + sizeof (Cimc_msg),
            MsgReceiveTimeOut);
      else
        ex = -1;
#endif
	}
	else {
	    CmsgBuf	b(sockFd); // Testing WS with socket connection.
	    if (OK != b.get()) return 1; // Unable to read a whole message.
	    // Note that we incur copy overhead only in test mode.
	    memcpy(pMaxMsg, (char *)&b, b.msgSize);
	}


	if (ex != OK) {
	    // The timeout is of the form EINTR
	    if (ex != EINTR)
#ifndef _GWSIM
		EXLOG(SEV_MINOR, EX_RECFAIL,ex,0,0,0);
#else
		ALTLOG(SEV_MINOR, EX_RECFAIL,ex,0,0,0);
#endif
	    // FREE THE MESSAGE - we are out of here!!!
	    FreeMsg(pMaxMsg);

	}
	else {
	    if ((pMaxMsg->code == MsgCode &&
		 pMaxMsg->seq == SequenceNumber) ||
		((MsgCode == 0) &&
		 (SequenceNumber == 0))) {
		fNotFound = FALSE;
		*pMsg = *pMaxMsg;  // copy over the header!!!

	    } // end if this is the one we are looking for


	    // we have a message - deal (as WF would say!)
	    if (pMaxMsg->MsgClass < IMC_CLASS_MAX &&
		MsgRouterTable [pMaxMsg->MsgClass].pMsgHandler != NULL) {
		ex = MsgRouterTable [pMaxMsg->MsgClass].pMsgHandler (pMaxMsg);
		if (ex) {
#ifndef _GWSIM
		    EXLOG (SEV_WARN,
			   EX_MSGHANDLER,
			   pMaxMsg->MsgClass,
			   IMC_CLASS_MAX,
			   pMaxMsg->code,
			   pMaxMsg->seq);
#else
		    ALTLOG (SEV_WARN,
			   EX_MSGHANDLER,
			   pMaxMsg->MsgClass,
			   IMC_CLASS_MAX,
			   pMaxMsg->code,
			   pMaxMsg->seq);
#endif
		    FreeMsg(pMaxMsg);
		}
	    } else {
#ifndef _GWSIM
		EXLOG (SEV_MINOR,
		       ex = EX_NOMSGHANDLER,
		       pMaxMsg->MsgClass,
		       IMC_CLASS_MAX,pMaxMsg->code,0);
#else
		ALTLOG (SEV_MINOR,
		       ex = EX_NOMSGHANDLER,
		       pMaxMsg->MsgClass,
		       IMC_CLASS_MAX,pMaxMsg->code,0);
#endif
		// FREE THE MESSAGE - we are out of here!!!
		FreeMsg(pMaxMsg);

	    }

	} /* end dealing with a message */
    }

    return (ex);
}

/****************************************************************************
 *Function: GetMsg
 *
 *Purpose: The purpose of this is to get any new message off the message
 *  queue and have it fill forwarded to the API that needs it.  If the
 *  calling routine passes it a 0 msgcode and a 0 sequence number, then
 *  any new message will trigger a return.  The pMsg will always be filled
 *  out with the header of the message (or a Cimc_msg).  This way, the
 *  calling routine can determine what to do now, if a 0 msgcode and a 0
 *  sequence number was provided.
 *
 ****************************************************************************/
exc GetMsg (msg_class ServerClass,
	    int16 SequenceNumber,
	    msg_code MsgCode,
	    time_t Timeout)

{
    exc ex = OK;
    Boolean fNotFound = TRUE;
    time_t Now;
    int32 MsgReceiveTimeOut;
    Cimc_msg_max * pMaxMsg;

    while (fNotFound && ex == OK) {

	if (Timeout != 0) {
	    //
	    time(&Now);
	    if (Now < Timeout) {
		MsgReceiveTimeOut = (Timeout - Now) * 1000; // Milliseconds
	    } else
		MsgReceiveTimeOut = 0;  // get whatever is there!
	} else
	    // wait forever!!!
	    MsgReceiveTimeOut = -1;


	pMaxMsg = MallocMsg( );
	if (pMaxMsg == NULL) {
#ifndef _GWSIM
	    EXLOG (SEV_MAJOR,EX_MALLOCFAIL,ServerClass,MsgCode,
		   SequenceNumber,0);
#else
	    ALTLOG (SEV_MAJOR,EX_MALLOCFAIL,ServerClass,MsgCode,
		   SequenceNumber,0);
#endif
	    return (ERC_OUTOFMEMORY);
	}

	const int	maxMsg = IMC_MAX_BODYSIZE + sizeof (Cimc_msg);
	if (! sockFd) {
	    // `Normal' server testing: use mailboxes:
	    if (IsMyMsgHere (ServerClass,
			     MsgCode,
			     SequenceNumber)) {

        // DaveS 6/17/99
        // We don't need our malloc'd message now...
        FreeMsg(pMaxMsg);

		    break; // we are done!!!
      }
#if defined(_GWSIM)
    if (!theNetwork_ms[server_index]) {
      Sleep(10);
      ex = EINTR;
    }
    else
      ex = ((CGwNetwork*)theNetwork)->CheckForMsg(pMaxMsg, Timeout, clientMB);
#else
	    ex = clientMB.receive((*pMaxMsg), maxMsg,MsgReceiveTimeOut);
#endif
	}
	else {
	    CmsgBuf	b(sockFd); // Testing WS with socket connection.
	    if (OK != b.get()) return 1; // Unable to read a whole message.
	    // Note that we incur copy overhead only in test mode.
	    memcpy(pMaxMsg, (char *)&b, b.msgSize);
	}

	if (ex != OK) {
	    // The timeout is of the form EINTR
	    if (ex != EINTR) {
#ifndef _GWSIM
		EXLOG(SEV_MINOR, 0,ex,0,0,0);
#else
		ALTLOG(SEV_MINOR, 0,ex,0,0,0);
#endif
	    } else {
		// we if we are done ...
		time (&Now);
		if (Now < Timeout) {
		    /* we need to see if our message is here yet*/
		    ex = OK;
		}
	    }
	    // FREE THE MESSAGE - will realloc at the tome
	    FreeMsg(pMaxMsg);
	}
	else {
	    if ((pMaxMsg->MsgClass == ServerClass &&
		 pMaxMsg->code == MsgCode &&
		 pMaxMsg->seq == SequenceNumber) ||
		((ServerClass == 0) &&
		 (MsgCode == 0) &&
		 (SequenceNumber == 0))) {
		// THIS IS THE MESSAGE WE ARE LOOKING FOR
		fNotFound = FALSE;

	    } // end if this is the one we are looking for

	    // we have a message - deal (as WF would say!)
	    if (pMaxMsg->MsgClass < IMC_CLASS_MAX &&
		MsgRouterTable [pMaxMsg->MsgClass].pMsgHandler != NULL) {
#if 0
		// code to debug who is recieving messages in the VUI
		if (!(pMaxMsg->code == 0x15 && pMaxMsg->MsgClass == 9))
		    EXLOG (SEV_WARN,0,pthread_self ( ),
			   pMaxMsg->MsgClass,pMaxMsg->code,0);
		// End of code to debug who is recieving messages in the VUI
#endif
		ex = MsgRouterTable [pMaxMsg->MsgClass].pMsgHandler (pMaxMsg);
		if (ex) {
#ifndef _GWSIM
		    EXLOG (SEV_WARN,
			   EX_MSGHANDLER,
			   pMaxMsg->MsgClass,
			   IMC_CLASS_MAX,
			   pMaxMsg->code,
			   pMaxMsg->seq);
#else
		    ALTLOG (SEV_WARN,
			   EX_MSGHANDLER,
			   ex,
			   pMaxMsg->MsgClass,
			   pMaxMsg->code,
			   pMaxMsg->seq);
#endif
		    FreeMsg( pMaxMsg );
		}
		// if we are looking for a specific message, and we
		// get an error on a different message. ... we really
		// do not give a damn, because we are looking for
		// a different message!
		if (fNotFound) {
		    ex = 0;
		}

	    } else {
#ifndef _GWSIM
		EXLOG (SEV_MINOR,
		       ex = EX_NOMSGHANDLER,
		       pMaxMsg->MsgClass,
		       IMC_CLASS_MAX,0,0);
#else
		ALTLOG (SEV_MINOR,
		       ex = EX_NOMSGHANDLER,
		       pMaxMsg->MsgClass,
		       IMC_CLASS_MAX,0,0);
#endif
		// FREE THE MESSAGE - will realloc at the tome
		FreeMsg(pMaxMsg);
	    }

	} /* end dealing with a message */
    } /* while looking for a message */

    return (ex);
}


//CsiStatus SysStatus;
#define REMOTE_CLIENT "REMOTE_VP"
Cimc_clientMB RemoteRcv_MB [MAX_UNITS_PER_SYSTEM];
//static mbId_t RemoteMBox [MAX_UNITS_PER_SYSTEM] = {0,0,0,0,0,0,0,0,0};

#define MAXWAITREV   5
#define WAITINC      1000
/****************************************************************************
 *Function: SendRemoteMsg
 *
 *Purpose: this funtion will send a message to a given remote unit
 *  if the send fails, it will query the address again to make sure
 *  that the unit did not go away.
 ****************************************************************************/
exc SendRemoteMsg (unit_t DestUnit,
		   Cimc_msg * pMsg,
		   Boolean fUseDefaultMBox)
{
    exc ex = OK;
    mbId_t RemoteMBox = 0;

    if (DestUnit >= 0 &&
	DestUnit < MAX_UNITS_PER_SYSTEM) {

	if (RemoteMBox == 0) {
	    // if system is down, do not bother
#if 0
	    if (SysStatus.table->unitStatus[DestUnit].baseStatus != stat_ok) {
		return (EX_UNITDOWN);
	    }
#endif
	    ex = imc_rte.queryServer(pMsg->MsgClass,
				     DestUnit,
				     RemoteMBox);
	    if (ex != OK) {
#ifndef _GWSIM
		EXLOG (SEV_WARN, EX_QUERYSERV2,ex,pMsg->MsgClass,
		       DestUnit,0);
#else
		ALTLOG (SEV_WARN, EX_QUERYSERV2,ex,pMsg->MsgClass,
		       DestUnit,0);
#endif
		return (ex);
	    }
	}

	pMsg->dst = RemoteMBox;
	if (fUseDefaultMBox)
	    pMsg->src = RemoteRcv_MB[DestUnit].getMbId();
	ex = RemoteRcv_MB[DestUnit].request((*pMsg));

	if (ex != OK) {
	    RemoteMBox = 0;
#if 0
	    if (SysStatus.table->unitStatus[DestUnit].baseStatus != stat_ok) {
		return (EX_UNITDOWN);
	    }
#endif
	    ex = imc_rte.queryServer(pMsg->MsgClass,
				     DestUnit,
				     RemoteMBox);
	    if (ex == OK) {
		pMsg->dst = RemoteMBox;

		ex = RemoteRcv_MB[DestUnit].request((*pMsg));
		if (ex) {
		    // OK, we lost the unit log it and continue
#ifndef _GWSIM
		    EXLOG (SEV_WARN, EX_REQFAIL,ex,0,0,0);
#else
		    ALTLOG (SEV_WARN, EX_REQFAIL,ex,0,0,0);
#endif
		}
	    } else {
#ifndef _GWSIM
		EXLOG (SEV_WARN, EX_QUERYSERV2,ex,0,0,0);
#else
		ALTLOG (SEV_WARN, EX_QUERYSERV2,ex,0,0,0);
#endif
	    }
	}

    } else {
#ifndef _GWSIM
	EXLOG (SEV_WARN,ex = EX_INVALIDUNIT,DestUnit,0,0,0);
#else
	ALTLOG (SEV_WARN,ex = EX_INVALIDUNIT,DestUnit,0,0,0);
#endif
    }
    return (ex);
}


/****************************************************************************
 *Function: SnaSendRemoteMsg
 *
 *Purpose: this funtion will send a message to a given remote unit
 *  if the send fails, it will query the address again to make sure
 *  that the unit did not go away.
 ****************************************************************************/
exc SnaSendRemoteMsg (unit_t DestUnit,
	              Cimc_msg * pMsg,
		      Boolean fUseDefaultMBox)
{
    exc ex = OK;
    mbId_t RemoteMBox = 0;

    if (DestUnit >= 0 &&
	DestUnit < MAX_UNITS_PER_SYSTEM) {

	if (RemoteMBox == 0) {
	    // if system is down, do not bother
#if 0
	    if (SysStatus.table->unitStatus[DestUnit].baseStatus != stat_ok) {
		return (EX_UNITDOWN);
	    }
#endif
	    ex = imc_rte.queryServer(pMsg->MsgClass,
				     DestUnit,
				     RemoteMBox);
	    if (ex != OK) {
#ifndef _GWSIM
		EXLOG (SEV_WARN, EX_QUERYSERV2,ex,pMsg->MsgClass,
		       DestUnit,0);
#else
		ALTLOG (SEV_WARN, EX_QUERYSERV2,ex,pMsg->MsgClass,
		       DestUnit,0);
#endif
		return (ex);
	    }
	}

	pMsg->dst = RemoteMBox;
	if (fUseDefaultMBox)
#if !defined(_GWSIM)
            pMsg->src = clientMB.getMbId(); /* Added by Ray */
#else
            pMsg->src = clientMB->getMbId(); /* Added by Ray */
#endif
/*      pMsg->src = RemoteRcv_MB[DestUnit].getMbId(); */
	ex = RemoteRcv_MB[DestUnit].request((*pMsg));

	if (ex != OK) {
	    RemoteMBox = 0;
#if 0
	    if (SysStatus.table->unitStatus[DestUnit].baseStatus != stat_ok) {
		return (EX_UNITDOWN);
	    }
#endif
	    ex = imc_rte.queryServer(pMsg->MsgClass,
				     DestUnit,
				     RemoteMBox);
	    if (ex == OK) {
		pMsg->dst = RemoteMBox;

		ex = RemoteRcv_MB[DestUnit].request((*pMsg));
		if (ex) {
		    // OK, we lost the unit log it and continue
#ifndef _GWSIM
		    EXLOG (SEV_WARN, EX_REQFAIL,ex,0,0,0);
#else
		    ALTLOG (SEV_WARN, EX_REQFAIL,ex,0,0,0);
#endif
		}
	    } else {
#ifndef _GWSIM
		EXLOG (SEV_WARN, EX_QUERYSERV2,ex,0,0,0);
#else
		ALTLOG (SEV_WARN, EX_QUERYSERV2,ex,0,0,0);
#endif
	    }
	}

    } else {
#ifndef _GWSIM
	EXLOG (SEV_WARN,ex = EX_INVALIDUNIT,DestUnit,0,0,0);
#else
	ALTLOG (SEV_WARN,ex = EX_INVALIDUNIT,DestUnit,0,0,0);
#endif
    }
    return (ex);
}



/****************************************************************************
 *Function: ReceiveRemoteCPMsg
 *
 *Purpose:
 ****************************************************************************/
exc GetRemoteMsg (unit_t SourceUnit,
		  msg_class ServerClass,
		  int16 SequenceNumber,
		  msg_code MsgCode,
		  time_t Timeout)
{
    exc ex = OK;
    Boolean fFoundMsg = FALSE;
    int nRevs = 0;
    Cimc_msg_max * pMaxMsg = NULL;
    time_t Now = time (0);
    Boolean fAllocatedMsg = FALSE;
    mbId_t RemoteMBox = 0;

    if (IsMyMsgHere (ServerClass,
		     MsgCode,
		     SequenceNumber))
    {
	return (0);
    }

    while (!fFoundMsg && ex == OK) {
	if (!fAllocatedMsg) {
	    pMaxMsg = MallocMsg ( );
	    fAllocatedMsg = TRUE;
	    if (pMaxMsg == NULL) {
#ifndef _GWSIM
		EXLOG (SEV_MAJOR,EX_MALLOCFAIL,ServerClass,MsgCode,
		       SequenceNumber,SourceUnit);
#else
		ALTLOG (SEV_MAJOR,EX_MALLOCFAIL,ServerClass,MsgCode,
		       SequenceNumber,SourceUnit);
#endif
		return (ERC_OUTOFMEMORY);   // ERROR ERROR - RETURN
	    }
	}

	ex = RemoteRcv_MB[SourceUnit].receive((*pMaxMsg),
					   IMC_MAX_BODYSIZE + sizeof (Cimc_msg),
					   WAITINC);  // Only wait one second

	if (!ex) {
	    if ((pMaxMsg->MsgClass == ServerClass &&
		 pMaxMsg->code == MsgCode &&
		 pMaxMsg->seq == SequenceNumber) ||
		((ServerClass == 0) &&
		 (MsgCode == 0) &&
		 (SequenceNumber == 0))) {
		// THIS IS THE MESSAGE WE ARE LOOKING FOR
		fFoundMsg = TRUE;

	    } // end if this is the one we are looking for

	    // we have a message - deal (as WF would say!)
	    if (pMaxMsg->MsgClass < IMC_CLASS_MAX &&
		MsgRouterTable [pMaxMsg->MsgClass].pMsgHandler != NULL) {
		ex = MsgRouterTable [pMaxMsg->MsgClass].pMsgHandler (pMaxMsg);
 		if (ex) {
		    // if we got an error here, then we are probably out
		    // of sync.  Get rid of this one, and continue!
#ifndef _GWSIM
		    EXLOG (SEV_WARN,
			   ex = EX_OLDMSGRCVD,
			   pMaxMsg->MsgClass,
			   pMaxMsg->seq,
			   pMaxMsg->code,0);
#else
		    ALTLOG (SEV_WARN,
			   ex = EX_OLDMSGRCVD,
			   pMaxMsg->MsgClass,
			   pMaxMsg->seq,
			   pMaxMsg->code,0);
#endif

		    FreeMsg (pMaxMsg);
		    fAllocatedMsg = FALSE; // we freed it
		    ex = OK; // we need to continue looking
		} else
		    fAllocatedMsg = FALSE; // If I consume it I do not free it
	    } else {
#ifndef _GWSIM
		EXLOG (SEV_MINOR,
		       ex = EX_NOMSGHANDLER,
		       pMaxMsg->MsgClass,
		       IMC_CLASS_MAX,0,0);
#else
		ALTLOG (SEV_MINOR,
		       ex = EX_NOMSGHANDLER,
		       pMaxMsg->MsgClass,
		       IMC_CLASS_MAX,0,0);
#endif
	    }
	} else {
	    // OK, we did not recieve any msg... is the unit still avail
	    if (IsMyMsgHere (ServerClass,
			     MsgCode,
			     SequenceNumber))
	    {
		ex = 0; // we found it
		FreeMsg (pMaxMsg);
		fAllocatedMsg = FALSE; // we freed it
		fFoundMsg = TRUE;
		break; // we are done!!!
	    }

	    if (Now + (++nRevs * WAITINC/1000)  > Timeout) {
#ifndef _GWSIM
		EXLOG (SEV_WARN,EX_MSGTIMEOUT,
		       SourceUnit, pMaxMsg->MsgClass, pMaxMsg->code, SequenceNumber);
#else
		ALTLOG (SEV_WARN,EX_MSGTIMEOUT,
		       SourceUnit, pMaxMsg->MsgClass, pMaxMsg->code, SequenceNumber);
#endif
		ex = ERC_TIMEOUT;
	    } else {
#if 0
		if (
		    SysStatus.table->unitStatus[SourceUnit].baseStatus != stat_ok) {
		    EXLOG (SEV_WARN,EX_UNITDOWN,SequenceNumber,
			   pMaxMsg->seq,SourceUnit,0);
		    ex = EX_UNITDOWN;
		}
#endif
		ex = imc_rte.queryServer(ServerClass,
					 SourceUnit,
					 RemoteMBox);
		if (ex) {
#ifndef _GWSIM
		    EXLOG (SEV_WARN,0,SequenceNumber,
			   pMaxMsg->seq,SourceUnit,0);
#else
		    ALTLOG (SEV_WARN,0,SequenceNumber,
			   pMaxMsg->seq,SourceUnit,0);
#endif
		    RemoteMBox = 0;
		}

	    }

	}

    } // while we are waiting

    if (ex &&
	fAllocatedMsg) {
	FreeMsg (pMaxMsg);
    }


    return (ex);

}






/****************************************************************************
 *Function: Initialize
 *
 *Purpose:
 ****************************************************************************/
resp_t InitRemoteMsging (int16 nMaxConcurrentRequests,
			 Boolean fIsDBUnit)
{
    exc ex = OK;
    static Boolean fInitialized = FALSE;
    int pid;
    char ClientQueue[50];
#if 0
    // We will not be sending messages
    if (!fIsMultiUnitSystem)
	return (OK);

#endif
    // allocate the outstanding request table and initialise it !!
    if (!fInitialized) {


	if (!ex) {
#if 0
	    ex = SysStatus.attach ( );
#endif
	    if (ex == OK) {
		if (!fComInit) {
		    // already done from the basic initialize
		    ex = imc_rte.initialize(false);
		    if (ex != OK) {
#ifndef _GWSIM
			EXLOG (SEV_MAJOR, EX_RTEINIT,ex,0,0,0);
#else
			ALTLOG (SEV_MAJOR, EX_RTEINIT,ex,0,0,0);
#endif
		    }
		}

		if (!ex) {
		    pid = getpid();
		    strcpy (ClientQueue, REMOTE_CLIENT);

		    cm_itoa (&ClientQueue [strlen (ClientQueue)], pid);
		    int SaveLen = strlen (ClientQueue);
		    for (int i = 0; i < MAX_UNITS_PER_SYSTEM; i++) {
			if (!fIsDBUnit) {
			    if (!(i == MP_UNIT_PRIMARY ||
				  i == imc_rte.thisUnit())) {
				continue; // only init this unit and NS
			    }

			}
			cm_itoa (&ClientQueue [SaveLen], i);
			ex = RemoteRcv_MB[i].registerName(ClientQueue);
			if (ex)
#ifndef _GWSIM
			    EXLOG (SEV_WARN,EX_CANNOTREGNAME,ex,
				   0,0,0);
#else
			    ALTLOG (SEV_WARN,EX_CANNOTREGNAME,ex,
				   0,0,0);
#endif
		    }

		}



	    } else
#ifndef _GWSIM
		EXLOG (SEV_WARN,EX_CANNOTATTTOSTA,ex,
		       0,0,0);
#else
		ALTLOG (SEV_WARN,EX_CANNOTATTTOSTA,ex,
		       0,0,0);
#endif
	}
	if (!ex)
	    fInitialized = TRUE;
    }


    if (ex)
	return (99);
    else
	return (OK);
}

/****************************************************************************
 *Function: MallocMsg
 *
 *Purpose: Creates a new message buffer that is big enough to hold any
 *         message.
 *
 *Usage:   CWSLoginReqMsg * pLogMsg;
 *         pLogMsg = (CWSLoginReqMsg *) MallocMsg();
 *         // Use the message
 *         FreeMsg(pLogMsg);
 *
 *         Ordinarily, the messaging layer will alloc a message and queue
 *         it. Then the API layer will de-queue it, take data out of the
 *         message and then call FreeMsg to delete it. On Lynx, instead
 *         calling new to alloc a message, there will be some kind of pool
 *         messages that will be re-used over and over.
 ****************************************************************************/
// static int nMsgs = 0;
Cimc_msg_max * MallocMsg(void)
{

//    EXLOG (SEV_INFO,0,nMsgs++,0,0,0);

    //CR15085 need to initialize the buffer.
    //return((Cimc_msg_max *)malloc(sizeof(Cimc_msg_max)));

    Cimc_msg_max * pMsg = (Cimc_msg_max *) 0;

    if(   (pMsg = (Cimc_msg_max *) malloc(sizeof(Cimc_msg_max)))
	!= (Cimc_msg_max *) 0 )
    {
        memset(pMsg, '\0', sizeof(Cimc_msg_max) );
    }

    return(pMsg);
}

/****************************************************************************
 *Function: FreeMsg
 *
 *Purpose:  Deletes a message created by MallocMsg. It takes a Cimc_msg * so
 *          that the caller can send in a pointer that is subclassed
 ****************************************************************************/
void FreeMsg(Cimc_msg * pMsg)
{

//    EXLOG (SEV_INFO,0,nMsgs--,pMsg->MsgClass,pMsg->code,0);
    free (pMsg);
}

#if defined(_GWSIM)
//
// Used by socknet, which we don't use but we do link with indirectly,
// so define this to make linker happy.
//
uInt16 HandleAsyncMsg(void *pBuff);	// Prototype, to quiet CW5
uInt16 HandleAsyncMsg(void *pBuff)
{
	return 0;
}
#endif

/****************************************************************************
                             CLIENT-SPECIFIC VERSIONS
****************************************************************************/

#else // LYNX

/****************************************************************************
 *Function: lock
 *
 *Purpose:
 ****************************************************************************/
static void lock() {}
/****************************************************************************
 *Function: unlock
 *
 *Purpose:
 ****************************************************************************/
static void unlock() {}
/****************************************************************************
 *Function: initlock
 *
 *Purpose:
 ****************************************************************************/
static void initlock() { }


/****************************************************************************
 *Function: SetUpForCommunication
 *
 *Purpose:
 ****************************************************************************/
exc SetUpForCommunication (char * pName)
{
  return ( SetUpForCommunication () );
}


/****************************************************************************
 *Function: SetUpForCommunication
 *
 *Purpose:
 ****************************************************************************/
exc SetUpForCommunication (void)
{
  return(OK);
}

/****************************************************************************
 *Function: SendMsg
 *
 *Purpose:
 ****************************************************************************/
uInt16 SendMsg (Cimc_msg * pMsg)
{
  // Call the network object to send the message.
  return((uInt16) theNetwork->SendMsg(pMsg, pMsg->msgSize));
}


/*
FUNCTIONHEADER+
****************************************************************
Function:

  GetMsg()

Description:

  This is the platform-dependant definition of GetMsg(). I malloc a message.
  Then I go into a loop. In the loop I check to see if a message arrived
  on the network. If so, I send it to a message handler. If it was the
  message Im waiting for then I break out of the loop. If it wasnt the
  one I was waiting for, I malloc another message and continue checking.
  I need to do this because the message handlers always enqueue the message
  somewhere for later processing. If we exceed timeout while waiting then I
  also break out of the loop. At the end I check to see if I need to free
  the temporary message I created in the beginning.

Syntax:
  RetCode = GetMsg(msg_class, seq, msgCode, timeout, pMsg);

Parameters:
IN
  int16 seqnum    The sequence number of response we're waiting for.
                    These should match up with seq num of sent message.
  msg_code msg    The particular type of message
  int16 timeout   The time at which we should time out while waiting for
                    message. This was figured out when we did the SendMsg()
		  If the timeout is zero, then we should wait forever.
OUT

Return Codes:

History:

Date        Who                 What
----------  ------------------	-------------------------------
12/27/93    wfenton  	        Created
1/27/94     wfenton             Took out msg parameters. Its alloced here

****************************************************************
FUNCTIONHEADER-
*/

// TEMP WF, We might want to be smarter about timeout. some msgs
// will take a longer time, like report queries. Maybe allow
// timeout to be passed different for different API calls

exc GetMsg (msg_class ServerClass,
	    int16 SequenceNumber,
               msg_code MsgCode,
               time_t Timeout)
{
  uInt16         err = OK;
  BOOL           foundMsg      = FALSE; // found any old message
  BOOL           foundRightMsg = FALSE; // found msg were looking for
  BOOL           fFreeMsg;
  BOOL           fEventMsg = FALSE;
  Cimc_msg_max * pMsg;

  if((pMsg = MallocMsg()) == (Cimc_msg_max *) 0)
  {
    return((exc) ERC_OUTOFMEMORY);
  }

  // unless dealt with, well free this message at the end
  fFreeMsg = TRUE;

  // while there is no error and we haven't seen msg we're looking for
  while(err == OK && !foundRightMsg)
  {

      if (!fRespInit) {
	  err = ERC_SRVRNOTACTIVE; // we cannot get any message we are shutting down.
	  break; // we are out of here

      }
    // First make a check to see if message is just waiting in the queue.
    // (used mostly if nested API left it there behind our backs.
    if (IsMyMsgHere (ServerClass,
                     MsgCode,
                     SequenceNumber))
    {
      foundRightMsg = TRUE;
      break; // we are done!!!
    }

    /* do a non-blocking check to see if a message is waiting */
    err = theNetwork->CheckForMsg(pMsg,
			       sizeof(*pMsg),
			       Timeout,
			       &foundMsg);
    if(foundMsg)
    {
      // we have a message, send to registered handler
      if (pMsg->MsgClass < IMC_CLASS_MAX &&
          MsgRouterTable [pMsg->MsgClass].pMsgHandler != NULL)
      {
	fEventMsg = (pMsg->type == IMC_MSG_EVENT);
        err = (uInt16) MsgRouterTable [pMsg->MsgClass].pMsgHandler (pMsg);
      }
      else
      {
        TRACE0("GetMsg: Internal error. Bad Message class\n");
        err = ERC_BADMESSAGE;
      }

      // If it was the specific message we wanted, return success
      if(err == OK &&
	 !fEventMsg &&
         pMsg->MsgClass == ServerClass &&
	 pMsg->code == MsgCode &&
         int16(pMsg->seq) == SequenceNumber)
      {
         foundRightMsg = TRUE;
         fFreeMsg      = FALSE;
      }
      else if(err == OK)
      {
        // It wasnt our message, so malloc another one and keep checking
        if((pMsg = MallocMsg()) == (Cimc_msg_max *) 0)
        {
          fFreeMsg = FALSE;
          err      = ERC_OUTOFMEMORY;
        }
        else
        {
          fFreeMsg = TRUE;
        }
      }
    }	// if(checkForMsg())
    else
    {
      // Check for timeout condition
      if((Timeout != (time_t) 0) &&
         (time((time_t *) NULL) > Timeout))
      {
        err = (exc) ERC_TIMEOUT;
      }
    } /* end dealing with a message */

  } // while(!err && !found)

  // If a handler didnt enqueue the message (timeout or error), we free it
  if(fFreeMsg)
  {
    FreeMsg(pMsg);
  }

  return((exc) err);
}

/*************************************************************************
Function:

  HandleAsyncMsg()

Description:

  This routine is used to handle asynchronous messages that arrive.
  The normal case is that the API functions come down and we
  synchronously deal with the message by calling the underlying network
  layer. But in the asynchronous case, it is the underlying network
  layer that receives the message so it has to then send it back to us
  to enqueue for later handling.

*************************************************************************/
uInt16 HandleAsyncMsg(void *pBuff);	// Prototype, to quiet CW5
uInt16 HandleAsyncMsg(void *pBuff)
{
  Cimc_msg_max *  pMsg;
  WFErc           err = WF_OK;

  ASSERT(pBuff);

  if((pMsg = MallocMsg()) == (Cimc_msg_max *) 0)
  {
    return(ERC_OUTOFMEMORY);
  }

  // make local copy of the message
  memcpy(pMsg, pBuff, (uInt16)((Cimc_msg *) pBuff)->msgSize); // 8/22/96 gah Mac Port: cast to get swap

  TRACE2("Routing Async message class[%d] code[%d]\n",
         (int) pMsg->MsgClass, (int) pMsg->code);

  // we have a message send to registered handler
  if (pMsg->MsgClass < IMC_CLASS_MAX &&
      MsgRouterTable [pMsg->MsgClass].pMsgHandler != NULL)
  {
    err = (uInt16) MsgRouterTable [pMsg->MsgClass].pMsgHandler (pMsg);
  }
  else
  {
    TRACE0("GetMsg: Internal error. Bad Message class\n");
    FreeMsg(pMsg);
    err = ERC_BADMESSAGE;
  }

  return(err);
}

/****************************************************************************
 *Function: MallocMsg
 *
 *Purpose: Creates a new message object that is big enough to hold any
 *         message.
 *
 *Usage:   CWSLoginReqMsg * pLogMsg;
 *         pLogMsg = (CWSLoginReqMsg *) MallocMsg();
 *         // Use the message
 *         Freemsg(pLogMsg);
 *
 *         Ordinarily, the messaging layer will alloc a message and queue
 *         it. Then the API layer will de-queue it, take data out of the
 *         message and then call FreeMsg to delete it.
 ****************************************************************************/
Cimc_msg_max * MallocMsg(void)
{
  Cimc_msg_max * pMsg = (Cimc_msg_max *) 0;

#ifndef __MWERKS__  // 8/20/96 gah Mac Port: only check for __MWERKS__, not macintosh
  const size_t size = sizeof(Cimc_msg_max);
#else
  const size_t size = sizeof(CmsgBuf);	/* Mac uses a slightly larger but handy class */
#endif

  if((pMsg = (Cimc_msg_max *) malloc(size)) != (Cimc_msg_max *) 0)
  {
    memset(pMsg, '\0', size);
  }

  return(pMsg);
}

/****************************************************************************
 *Function: FreeMsg
 *
 *Purpose:  Deletes a message created by MallocMsg. It takes a Cimc_msg * so
 *          that the caller can send in a pointer that is subclassed
 ****************************************************************************/
void FreeMsg(Cimc_msg * pMsg)
{
   free((void *) pMsg);
}

#endif /* MSWINDOWS */
