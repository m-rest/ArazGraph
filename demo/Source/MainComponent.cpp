/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "ArazGraph.h"

using namespace arazGraph;


//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (800, 600);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    ArazGraph* graph = new ArazGraph(getLocalBounds(), "Title", "X Label", "Y Label", Colours::black, Colours::white);
    Random* rnd = new Random();

    for (int j = 0; j < 100; j += 20)
    {
        ArazGraphDataset* leftEarData = new ArazGraphDataset("Left",
                                                              Colour::fromRGB(rnd->nextFloat() * 0xff,
                                                                              rnd->nextFloat() * 0xff,
                                                                              rnd->nextFloat() * 0xff));
        for (int i = 0; i < 5000; i += 10)
        {
            leftEarData->append(new ArazGraphPoint(i, j * sin(i / 200.0)));
        }
        graph->append(leftEarData);
    }
	
	ArazGraphDataset* rightEarData = new ArazGraphDataset("Right", Colours::red);
	rightEarData->append(new ArazGraphPoint(   0, 10));
	rightEarData->append(new ArazGraphPoint( 100, 10));
	rightEarData->append(new ArazGraphPoint( 500, 10));
	rightEarData->append(new ArazGraphPoint(1000, 50));
	rightEarData->append(new ArazGraphPoint(2000, 10));
	rightEarData->append(new ArazGraphPoint(5000, 10));
	graph->append(rightEarData);

    ArazGraphDataset* centreData = new ArazGraphDataset("Centre", Colours::yellow);
    centreData->append(new ArazGraphPoint(   0, 40));
    centreData->append(new ArazGraphPoint( 100, 40));
    centreData->append(new ArazGraphPoint( 500, 40));
    centreData->append(new ArazGraphPoint(1000, 40));
    centreData->append(new ArazGraphPoint(2000, 40));
    centreData->append(new ArazGraphPoint(5000, 40));
    graph->append(centreData);

    graph->paint(g);

    delete graph;
    delete rnd;
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    repaint();
}
