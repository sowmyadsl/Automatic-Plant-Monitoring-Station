# Plant.io
IOT Hackathon 2018, Puppet
By Sue Robbins, Daniel Phillips, Alex Weston, Olivia Cole, Sowmya Dinavahi

## Sustainable Futures 
Alex Weston

 - Problem: Although growing your own plants provides many benefits for a sustainable future, urban dwellers often have little exposure to gardening, so they may not know how to care for plants.
 - Benefits of growing plants:
   - Improved air quality
   - Some plants (spider plants) minimize allergens
   - Supplemental food source
   - Reduction in food transportation costs
   - Reduced stress
   - Basic education about gardening

Solution:
Plant.io can help by monitoring moisture and light levels, reminding you when it's time to water and giving visual and audible indications of the plant’s overall wellness.

## Demo
Daniel Phillips, Sowmya Dinavahi
### Adafruit.io dashboard
[Dashboard](https://io.adafruit.com/sowmyadsl/public)*

### Physical Setup:

![screenshot](https://github.com/sowmyadsl/Automatic-Plant-Monitoring-Station/blob/master/Photos/20180324_124542_HDR.jpg)

#### Wireframe:
![screenshot](https://github.com/sowmyadsl/Automatic-Plant-Monitoring-Station/blob/master/Photos/20180324_124611_HDR.jpg)

### Frontend UI Prototype:
![landing-page](https://github.com/sowmyadsl/Automatic-Plant-Monitoring-Station/blob/master/Photos/Landing-page.png)

## Challenges
Sue Robbins

 - Provided humidity sensor isn't suitable for measuring soil moisture, so we simulated this using a adafruit feed
 - Tactile button doesn't attach well to the board
 - Had trouble getting RGB LED to work

## Future Directions
Olivia Cole

 - Implement custom dashboard based on our prototype for better user experience 
 - Use a soil-specific moisture sensor to replace simulated sensor
 - Integrate a temperature monitor
 - Include email or push notifications when plant needs attention
 - More physical outputs to indicate plant health (LED diplay, servo-based flag)
 - Multi-plant monitoring



## Notes
\* dashboard feeds aren't displayed in public version of the dashboard