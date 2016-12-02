/*
 BEGIN_JUCE_MODULE_DECLARATION
 
    ID:               ArazGraph
    vendor:           m-rest
    version:          1.0.0
    name:             ArazGraph
    description:      This is a simple data plotter graph class for JUCE
    website:          https://github.com/m-rest/ArazGraph
    license:          Unknown, Copyright Ara Bedrossian

    dependencies:     juce_core juce_graphics

 END_JUCE_MODULE_DECLARATION
*/


#ifndef ARAZGRAPH_H_INCLUDED
#define ARAZGRAPH_H_INCLUDED

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>


namespace arazGraph
{
    using namespace juce;

    
    class ArazGraphPoint
    {
    public:
        ArazGraphPoint(float xValue, float yValue);

    public:
        float xValue;
        float yValue;
        LinkedListPointer<ArazGraphPoint> nextListItem;
    };
    

    class ArazGraphDataset
    {
    public:
        ArazGraphDataset(String label = "Dataset", Colour colour = Colours::black);
        ~ArazGraphDataset();
        void append(float xValue, float yValue);

    public:
        String label;
        Colour colour;
        LinkedListPointer<ArazGraphPoint>* points;
        LinkedListPointer<ArazGraphDataset> nextListItem;
    };

    class ArazGraph : public juce::Component
    {
    public:
        ArazGraph(String title = "Title", String xLabel = "X-Axis", String yLabel = "Y-Axis", Colour fgColour = Colours::black, Colour bgColour = Colours::white);
        ~ArazGraph();
        void append(ArazGraphDataset* dataset);
        void paint(Graphics& g);

    private:
        float getRoundedTickRange( unsigned int tickCount, float range);
        Rectangle<int> region;
        Rectangle<int> regionGraph;
        String title;
        String xLabel;
        String yLabel;
        Colour fgColour;
        Colour bgColour;
        int xMargin;
        int yMargin;
        LinkedListPointer<ArazGraphDataset>* datasets;
    };
}
#endif  // ARAZGRAPH_H_INCLUDED
