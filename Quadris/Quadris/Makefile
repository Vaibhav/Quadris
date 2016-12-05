CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = quadris
OBJECTS = main.o BlockFactory.o Board.o HeavyBlockDecorator.o GeneratorProbabilityDecorator.o GeneratorHeavyBlockDecorator.o GeneratorCentreBlockDecorator.o BlockParser.o Block.o BlockGenerator.o BlockGeneratorBase.o Game.o CommandInterpreter.o Subject.o Display.o info.o GraphicsDisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
