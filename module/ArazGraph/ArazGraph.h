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
        void append(ArazGraphPoint* point);

    public:
        String label;
        Colour colour;
        LinkedListPointer<ArazGraphPoint>* points;
        LinkedListPointer<ArazGraphDataset> nextListItem;
    };

    class ArazGraph
    {
    public:
        ArazGraph(Rectangle<int> region, String title = "Araz Graph", String xLabel = "X-Axis", String yLabel = "Y-Axis", Colour fgColour = Colours::white, Colour bgColour = Colours::navy);
        ~ArazGraph();
        void append(ArazGraphDataset* dataset);
        void paint(Graphics& g);

    private:
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
