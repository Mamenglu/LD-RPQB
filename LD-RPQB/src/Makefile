###############################################################################
### ~~~~~~~~~~~~~~~~~~~~~ SPARQL Benchmark Generator ~~~~~~~~~~~~~~~~~~~~~~ ###
###############################################################################
### ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Makefile  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ###
### ----------------------------------------------------------------------- ###
###                                                                         ###
### - Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008           ###
### - Copyright: See COPYING file that comes with this distribution         ###
###                                                                         ###
###############################################################################

# !!! ### WARNING:
# !!! If you want to generate comparable, "standard" documents (which
# !!! might be of interest to compare query result sizes), then do NOT use
# !!! optimization level -O3
# -> this is because -O3 (in contrast to -O2) is not semantics-preserving
#    (due to floating point optimizations); thus, when using -O3 (or higher),
#    the generator might create different documents, and results might differ 
CPP =  g++ -Wall -m64 -O2

SOURCES=main.cpp generator.cpp cmdline.cpp document.cpp article.cpp article_inpro.cpp institution.cpp inproceedings.cpp proceedings.cpp book.cpp incollection.cpp phdthesis.cpp mastersthesis.cpp www.cpp property.cpp propertymanager.cpp propertyabstract.cpp propertyaddress.cpp propertyauthor.cpp propertyaffect.cpp propertybooktitle.cpp propertycdrom.cpp propertychapter.cpp propertycite.cpp propertycoauthor.cpp propertycrossref.cpp propertyeditor.cpp propertyee.cpp propertyisbn.cpp propertyjournal.cpp propertymonth.cpp propertynote.cpp propertynumber.cpp propertypage.cpp propertypublisher.cpp propertyrecord.cpp propertyschool.cpp propertyseries.cpp propertytitle.cpp propertyurl.cpp propertyvolume.cpp propertyyear.cpp outputlimitmgr.cpp rdftriple.cpp rdfobject.cpp functions.cpp rdftriplepool.cpp journal.cpp gaussiandistribution.cpp namepool.cpp namepoolfile.cpp namepoolmgr.cpp randomnizer.cpp randomwww.cpp randomphd.cpp randommaster.cpp stringtools.cpp volumemgr.cpp activeauthors.cpp author.cpp propertyauthorname.cpp editor.cpp missingcites.cpp blindrdftriple.cpp instancelogger.cpp unknowndocmgr.cpp unknowndocument.cpp referencebagmgr.cpp referencebag.cpp referencebagreference.cpp publishers.cpp namemgr.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: rpqbenchgen

############################### binary
rpqbenchgen:	$(OBJECTS)
		$(CPP) $(OBJECTS) -o ./rpqbench_gen -lm

############################### objects
%.o: %.cpp
	$(CPP) $(CFLAGS) -c $<

############################### clean 
clean:
	rm -f *.o *~ rpqbench_gen
