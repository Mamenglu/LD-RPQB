//
// C++ Implementation: PropertyJournal
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertyjournal.h"

PropertyJournal::PropertyJournal(RDFTriple *main_triple, RDFTriple *_journal_triple) :
    Property(PROPERTY_JOURNAL, main_triple), journal_triple(_journal_triple)
{
}


PropertyJournal::~PropertyJournal()
{
}

/*!
    \fn PropertyJournal::calc()
 */
bool PropertyJournal::calc()
{
    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("swrc", "journal");
    RDFObject *o3 = new RDFObject(RDFObject::URIObj,
        journal_triple->getSubjectPtr()->getString());
    setObjs(o1, o2, o3);

    return true;
} //calc
