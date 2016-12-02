# ArazGraph

This is a simple data plotter [juce](https://github.com/julianstorer/JUCE)::Component with auto-scaling axes, organized as a JUCE module.

## Requirements

Tested with JUCE >4.0.0, might work with >3.0.0 as well.

## Example

```
MainContentComponent::MainContentComponent()
{
    addAndMakeVisible(graph);
    
    Random rnd;
    
    for (int dataset = 0; dataset < 5; dataset += 1)
    {
        ArazGraphDataset* leftEarData = new ArazGraphDataset("Amplitude: "+String(j),
                                                             Colour::fromRGB(rnd.nextFloat() * 0xff,
                                                                             rnd.nextFloat() * 0xff,
                                                                             rnd.nextFloat() * 0xff));
        for (int x = -550; x < 550; x += 10)
        {
            leftEarData->append( x, 50*dataset* sin(x / 200.0) );
        }
        graph.append(leftEarData);
    }
    
    setSize (800, 600);
}

void MainContentComponent::resized()
{
    graph.setBounds(getLocalBounds().reduced(10, 10));
    repaint();
}
```

## Screenshots

![Screenshot](doc/Screenshot.png)

## Authors

Original author: Ara Bedrossian

Improved and turned into a JUCE module by Maximilian Rest
