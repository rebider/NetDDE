/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		NETDDESVRPIPE.CPP
** COMPONENT:	The Application
** DESCRIPTION:	CNetDDESvrPipe class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CNetDDESvrPipe::CNetDDESvrPipe()
	: CNetDDEPipe(this)
{
	SetTimeOut(App.m_nNetTimeOut);
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CNetDDESvrPipe::~CNetDDESvrPipe()
{
	Close();

	// Cleanup.
	m_aoNetConvs.DeleteAll();
}

/******************************************************************************
** Method:		FindNetConv()
**
** Description:	Find the NetDDE conversation by its DDE conversation and ID.
**
** Parameters:	pConv	The DDE conversation.
**				nConvID	The conversation ID.
**
** Returns:		The NetDDE conversation or NULL.
**
*******************************************************************************
*/

CNetDDEConv* CNetDDESvrPipe::FindNetConv(CDDECltConv* pConv, uint32 nConvID) const
{
	// For all conversations...
	for (int j = 0; j < m_aoNetConvs.Size(); ++j)
	{
		CNetDDEConv* pNetConv = m_aoNetConvs[j];

		// Matches?
		if ((pNetConv->m_pSvrConv == pConv) && (pNetConv->m_nSvrConvID == nConvID))
			return pNetConv;
	}

	return NULL;
}

/******************************************************************************
** Method:		IsLinkUsed()
**
** Description:	Checks if the link is referenced by any of the connections'
**				conversations.
**
** Parameters:	pLink	The DDE link.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CNetDDESvrPipe::IsLinkUsed(CDDELink* pLink) const
{
	CDDEConv* pConv = pLink->Conversation();

	// For all conversations...
	for (int i = 0; i < m_aoNetConvs.Size(); ++i)
	{
		CNetDDEConv* pNetConv = m_aoNetConvs[i];

		// Ignore, if different conversation.
		if (pNetConv->m_pSvrConv != pConv)
			continue;

		// Conversation references link?
		if (pNetConv->m_aoLinks.Find(pLink) != -1)
			return true;
	}

	return false;
}
