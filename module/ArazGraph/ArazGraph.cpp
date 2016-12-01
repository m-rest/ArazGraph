/**
* @file   ArazGraph.cpp
* @Author Ara Bedrossian (info@arazconsulting.com)
* @date   April, 2016
* @brief  ArazGrpah a simple graph class for JUCE implementaion
*/
#include "ArazGraph.h"


namespace arazGraph
{
    
/**
 * Constructor function for the ArazGraphPoint class
 * @param xValue - x value of the point
 * @param yValue - y value of the point
 */
ArazGraphPoint::ArazGraphPoint(float xValue, float yValue)
{
    this->xValue = xValue;
    this->yValue = yValue;
}

/**
 * Constructor function for the ArazGraphDataset class
 * @param label - the lable for this dataset
 * @param colour - the colour which will be used to render this dataset
 */
ArazGraphDataset::ArazGraphDataset(String label, Colour colour)
{
    this->label = label;
    this->colour = colour;
    this->points = new LinkedListPointer<ArazGraphPoint>();
}

/**
 * Destructor function for ArazGraphDataset class
 */
ArazGraphDataset::~ArazGraphDataset()
{
	points->deleteAll();
    delete points;
}

/**
 * Appends a new point to this dataset
 * @param point - instantiated pointer to the point object which will be added to this dataset
 */
void ArazGraphDataset::append(ArazGraphPoint* point)
{
    points->append(point);
}

/**
 * Constructor function for the ArazGraph class
 * @param region -  the boundries of the graph
 * @param title - the graph title
 * @param xLabel - label for x axis
 * @param yLabel - label for y axis
 * @param Colour fgColour - foreground color
 * @param Colour bgColour - background color
 */
ArazGraph::ArazGraph(Rectangle<int> region, String title, String xLabel, String yLabel, Colour fgColour, Colour bgColour)
	: xMargin(-50), yMargin(-40)
{
	this->region = region;
	this->regionGraph = region;
	this->regionGraph.expand(xMargin, yMargin);
	this->title = title;
	this->xLabel = xLabel;
	this->yLabel = yLabel;
	this->fgColour = fgColour;
	this->bgColour = bgColour;
	this->datasets = new LinkedListPointer<ArazGraphDataset>();
}

/**
 * Destructor function for ArazGraph class
 */
ArazGraph::~ArazGraph()
{
	datasets->deleteAll();
    delete datasets;
}

/**
 * Appends a new dataset to this graph
 * @param dataset - instantiated pointer to the dataset object which will be added to this graph
 */
void ArazGraph::append(ArazGraphDataset* dataset)
{
    datasets->append(dataset);
}

/**
 * The main paint function which need to be embedded in parent paint method
 * @param g - parents instantiated graphics object
 */
void ArazGraph::paint(Graphics& g)
{
    g.fillAll(bgColour);

	float maxX = FLT_MIN;
	float minX = FLT_MAX;
	float maxY = FLT_MIN;
	float minY = FLT_MAX;
	int lineH = 1;

	ArazGraphDataset* dataset = datasets->get();
	ArazGraphPoint* point = NULL;
	while (dataset != NULL)
	{
		point = dataset->points->get();
		while (point != NULL)
		{
			if (point->xValue > maxX) maxX = point->xValue;
			if (point->yValue > maxY) maxY = point->yValue;
			if (point->xValue < minX) minX = point->xValue;
			if (point->yValue < minY) minY = point->yValue;
			point = point->nextListItem;
		}
		dataset = dataset->nextListItem;
	}
    
    float dx = getRoundedTickRange( 10, maxX-minX );
    float dy = getRoundedTickRange( 10, maxY-minY );
    
    minX = dx * roundf( minX / dx );
    maxX = dx * roundf( 1 + maxX / dx );
    
    minY = dy * roundf( minY / dy ) - dy;
    maxY = dy * roundf( 1 + maxY / dy ) - dy;
    
    
	float scaleX = regionGraph.getWidth() / ((maxX == minX ? 0.0001 : maxX - minX) * 1.10);
	float scaleY = regionGraph.getHeight() / ((maxY == minY ? 0.0001 : maxY - minY) * 1.10);
    
    // draw x-axis / grid
    g.setFont(Font(12.0f));
    g.setColour(fgColour);
    for (int i = 0; i < 11; i++)
    {
        int x = (scaleX * i * dx) + regionGraph.getBottomLeft().getX();
        int y = regionGraph.getBottomLeft().getY();
        int y0 = regionGraph.getTopLeft().getY();
        int value = minX + (dx * i);
        //Line<float> line(x, y, x, y0);
        //float len[] = { 6,8 };
        //g.drawDashedLine(line, len, 2, .5f);
        g.setColour(Colours::whitesmoke);
        g.drawLine(x, y, x, y0, 2.0f);
        g.setColour(fgColour);
        g.drawLine(x, y - 5, x, y + 5, 2);
        g.drawSingleLineText(String(value), x - 5, y + 20, Justification::left);
    }
    
    // draw y-axis / grid
    for (int i = 0; i < 11; i++)
    {
        int x = regionGraph.getTopLeft().getX();
        int y = regionGraph.getHeight() - (scaleY * i * dy) + regionGraph.getTopLeft().getY();
        int x0 = regionGraph.getTopRight().getX()-scaleX*dx;
        int value = minY + (dy * i);
        //Line<float> line(x, y, x0, y);
        //float len[] = { 6, 8 };
        //g.drawDashedLine(line, len, 2, .5f);
        g.setColour(Colours::whitesmoke);
        g.drawLine(x, y, x0, y, 2.0f);
        g.setColour(fgColour);
        g.drawLine(x - 5, y, x + 5, y, 2);
        g.drawSingleLineText(String(value), x - 10, y + 5, Justification::right);
    }

	// draw points
	dataset = datasets->get();
    while (dataset != NULL)
    {
		g.setColour(dataset->colour);
		point = dataset->points->get();
		int x = (scaleX * (point->xValue - minX)) + regionGraph.getX();
		int y = regionGraph.getHeight() - (scaleY * (point->yValue - minY)) + regionGraph.getY();
		int preX = x;
		int preY = y;
		while (point != NULL)
		{
			x = (scaleX * (point->xValue - minX)) + regionGraph.getX();
			y = regionGraph.getHeight() - (scaleY * (point->yValue - minY)) + regionGraph.getY();
			g.drawLine(preX, preY, x, y, 2);
			//g.fillRect(x - 1, y - 1, 3, 3);
			preX = x;
			preY = y;
			point = point->nextListItem;
		}
		g.drawSingleLineText(dataset->label, regionGraph.getTopRight().getX() - 5, regionGraph.getTopRight().getY() + (lineH * 18), Justification::right);
		lineH++;
		dataset = dataset->nextListItem;
    }

    // draw graph general elements
	g.setColour(fgColour);
	g.drawRect(regionGraph.withTrimmedRight(scaleX*dx), 2);
	
	g.setFont(Font(16.0f));
	g.setColour(fgColour);
	g.drawText(title, region, Justification::centredTop, true);
	
	g.setFont(Font(12.0f));
	g.setColour(fgColour);
	g.drawText(xLabel, region, Justification::centredBottom, true);
	g.addTransform(AffineTransform::identity.rotated(-float_Pi / 2.0, region.getCentreX(), region.getCentreY()));
	g.drawText(yLabel, region, Justification::centredTop, true);
}
 
    
/**
 * Returns a rounded tick range which helps to prepare a nice axis scaling
 * http://stackoverflow.com/questions/326679/choosing-an-attractive-linear-scale-for-a-graphs-y-axis
 * @param tickCount - number of desired ticks
 * @param range - range of the values to be displayed
*/
float ArazGraph::getRoundedTickRange( unsigned int tickCount, float range)
{
#if 0
    float unroundedTickSize = range/(tickCount-1);
    float x = std::ceil(std::log10(unroundedTickSize)-1);
    float pow10x = std::pow(10, x);
    float roundedTickRange = std::ceil(unroundedTickSize / pow10x) * pow10x;
#else
    // calculate an initial guess at step size
    float tempStep = range/tickCount;
        
    // get the magnitude of the step size
    float mag = (float)std::floor(std::log10(tempStep));
    float magPow = (float)std::pow(10, mag);
        
    // calculate most significant digit of the new step size
    float magMsd = (int)(tempStep/magPow + 0.5);
        
    // promote the MSD to either 1, 2, or 5
    if (magMsd > 5.0)
        magMsd = 10.0f;
    else if (magMsd > 2.0)
        magMsd = 5.0f;
    else if (magMsd > 1.0)
        magMsd = 2.0f;
        
    float roundedTickRange = magMsd*magPow;
#endif
    
    return roundedTickRange;
}

    
}
