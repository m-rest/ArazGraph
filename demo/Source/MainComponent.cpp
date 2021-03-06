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
    addAndMakeVisible(graph);
    
    Random rnd;
    
    for (int j = 000; j <= 550; j += 50)
    {
        ArazGraphDataset* leftEarData = new ArazGraphDataset("Amplitude: "+String(j),
                                                             Colour::fromRGB(rnd.nextFloat() * 0xff,
                                                                             rnd.nextFloat() * 0xff,
                                                                             rnd.nextFloat() * 0xff));
        for (int i = -550; i < 550; i += 10)
        {
            leftEarData->append( i, j * sin(i / 200.0) );
        }
        graph.append(leftEarData);
    }
    
    setSize (800, 600);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::transparentBlack);
}

void MainContentComponent::resized()
{
    graph.setBounds(getLocalBounds().reduced(10, 10));

    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    repaint();
}
