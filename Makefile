CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash
PROGRAMS=	measure uscheme uschemeSmart

all:		$(PROGRAMS)

measure:	measure.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

uscheme:	uscheme.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

uschemeSmart:	uschemeSmart.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(PROGRAMS)

test:		test-output test-memory test-time

test-output:	$(PROGRAMS)
	@echo "Testing output (uscheme)..."
	@diff --suppress-common-lines -y <(./uscheme -b      < input) output
	@echo "Testing output (uschemeSmart)..."
	@diff --suppress-common-lines -y <(./uschemeSmart -b < input) output

test-memory:	$(PROGRAMS)
	@echo "Testing memory (uscheme)..."
	@[ `valgrind --leak-check=full ./uscheme -b      < input 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]
	@echo "Testing memory (uschemeSmart)..."
	@[ `valgrind --leak-check=full ./uschemeSmart -b < input 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]

test-time:	$(PROGRAMS)
	@echo "Testing time (uscheme)..."
	@./measure ./uscheme -b      < input | tail -n 1 | awk '{ if ($$1 > 1.0) { print "Time limit exceeded"; exit 1} }'
	@echo "Testing time (uschemeSmart)..."
	@./measure ./uschemeSmart -b < input | tail -n 1 | awk '{ if ($$1 > 1.0) { print "Time limit exceeded"; exit 1} }'
