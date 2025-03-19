//
// C++ Implementation: Publishers
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "publishers.h"
#include "randomnizer.h"

char* Publishers::publishers[111]={
        "Academic Press",
        "ACM Press",
        "Addison Wesley",
        "American Academy of Arts and Sciences",
        "American Association of University Presses",
        "American Chemical Society",
        "American Institute of Physics Press",
        "Artech House",
        "Aztec Books",
        "Baltzer Science Publishers",
        "Benjamin/Cummings Publishers Co., Inc.",
        "BIOS Scientific Press",
        "Blackwell Publishers",
        "Books That Work",
        "British Library",
        "Business Communications Company, Inc.",
        "Butterworth-Heinemann",
        "Butterworth Legal Publishers",
        "Butterworths",
        "Cambridge University Press",
        "Carswell Publishing",
        "Chemical Abstracts Service",
        "CD Publishing Corporation",
        "ChemTec Publishing",
        "Circlet Press",
        "City Lights Publishers and Booksellers",
        "CMP Publications",
        "Cold Spring Harbor Laboratory Press",
        "Jacobs Publishing, Ltd.",
        "Jason Aronson Publishers",
        "Johns Hopkins University Press",
        "Kluwer Academic Publishers",
        "Koeltz Scientific Books",
        "Learned Information Ltd.",
        "Lehigh University Press",
        "Library Solutions Institute and Press",
        "Lonely Planet Books",
        "Macmillan Computer Publishing USA",
        "Manaaki Whenua Press",
        "Manchester University Press",
        "Math-Pro Press",
        "McGraw-Hill",
        "ME Sharpe",
        "Micro Focus Publishing",
        "Miller Freeman, Inc.",
        "Mitchell Beazley",
        "MIT Press",
        "Moon Travel Handbooks",
        "Morgan Kaufmann Publishers",
        "Motorola University Press",
        "Natural Literacy Publishers",
        "NCC Blackwell",
        "Nine Pines Publishing",
        "Nolo Press Self-Help Law Center",
        "Oceana Publications",
        "Oliver Books",
        "Open University Press",
        "OReilly & Associates",
        "Oxford University Press",
        "Pantera Publishing, Inc.",
        "Pathfinder Press",
        "Penguin Books Ltd",
        "Penguin USA",
        "Pluto Press Ltd",
        "Prentice Hall",
        "Princeton University Press",
        "Productivity Press",
        "Purple Training Ltd",
        "Quantum Books",
        "Random House, Inc.",
        "Raven Press Medical and Scientific Publishers",
        "Red Oak Media",
        "Reference Press",
        "Resolution Business Press",
        "Scholastic Inc.",
        "Sidran Foundation and Press",
        "SPIE Optical Engineering Press",
        "Springer-Verlag, Germany and New York",
        "SunSoft Press",
        "State University of New York Press",
        "Sybex",
        "Taigh na Teud",
        "Tanner Long Press, Inc.",
        "Telos",
        "Thomson Publishing",
        "Tor Books",
        "Twin Press",
        "UB & US Books & Things",
        "UCL Press",
        "Unisa Press",
        "University of California Press",
        "University of Chicago Press",
        "University of Illinois Press",
        "University of Michigan Press",
        "University of Minnesota Press",
        "University of North Carolina Press",
        "University of North London Press",
        "University of South Carolina Press",
        "University of Tennessee Press",
        "University of Texas Press",
        "University of Wisconsin Press",
        "Van Nostrand Reinhold",
        "Vermont AudioBooks",
        "Virtual Press",
        "Viking Penguin",
        "Ventana Press",
        "West Publishing Company",
        "Wiley",
        "Williams & Wilkins, Medical Publishers",
        "World Scientific Publishing",
        "Ziff-Davis Publishing"};

Publishers* Publishers::instance=0L;

Publishers::Publishers() {
}

Publishers* Publishers::getInstance() {
    if (instance==0L) {
        instance=new Publishers();
    }
    return instance;
}

Publishers::~Publishers() {
}

const char* Publishers::getRandomPublisher() {
    return publishers[Randomnizer::getInstance()->getRandomValue(111)];
}
