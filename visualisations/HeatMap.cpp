#include <tulip/TulipPluginHeaders.h>
#include <tulip/Color.h>
#include <tulip/ColorScale.h>
#include <tulip/IntegerProperty.h>
#include <tulip/ColorProperty.h>
#include <random>


using namespace tlp;
/**
* heat map implementation
* based on random values representing "frequency of path usage"
*/

class HeatMap: public ColorAlgorithm {
public:
    PLUGININFORMATION("Heat-Map Visualisation","Hedi Ghediri",
                    "06/04/2017","builds a heat map",
                    "1.0", "Heat-Map")
    HeatMap(const tlp::PluginContext* context): ColorAlgorithm(context) {
        parameters.setDirection("result", tlp::INOUT_PARAM);
    }
    
    bool run() {
        // random frequency values because integration with bike data isn't achieved yet
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0., 1.);
        auto nextHopProperty = graph->getLocalProperty<tlp::IntegerVectorProperty>("nextHop");
        // auto result = graph->getLocalProperty<tlp::ColorProperty>("viewColor");
        result->setAllNodeValue(tlp::Color(0, 255, 0, 255));
        result->setAllEdgeValue(tlp::Color(128, 128, 128, 128));
       
        auto heatMap = tlp::ColorScale(
            std::vector<tlp::Color>{tlp::Color::Red, tlp::Color::Blue, tlp::Color::Yellow}, true
        );
        
        auto edges = graph->getEdges();
        while (edges->hasNext()) {
            auto edge = edges->next();
            if (!nextHopProperty->getEdgeValue(edge).empty()) {
                result->setEdgeValue(edge, heatMap.getColorAtPos(dist(mt)));
            }
        }
        
        delete edges; 
        return true;
    }
};
PLUGIN(HeatMap)
