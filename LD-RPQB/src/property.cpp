//
// C++ Implementation: Property
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "property.h"

/**
 * Constructor
 * @param _type type id of property, as defined in @ref property.h
 * @param _main_triple type definition triple, to which this attribute relates
 */
Property::Property(unsigned _type, RDFTriple *_main_triple)
    : type(_type), main_triple(_main_triple)
{
}

Property::~Property()
{
}
