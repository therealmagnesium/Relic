#include <Relic.h>
using namespace Relic;

// Make an app class that inherits from Relic::Application
class LoggingApp : public Application
{
public:
    LoggingApp();

    /* OnStart()
     *      - [REQUIRED]
     *      - Called once, when the app is initialized
     *      - Used for initializing entities and other game objects
     */
    void OnStart() override;

    /* OnUpdate()
     *      - [REQUIRED]
     *      - Called once per frame
     *      - Used for:
     *              - Collisions / physics
     *              - Movement
     */
    void OnUpdate() override;

    /* OnRender()
     *      - [REQUIRED]
     *      - Called once per frame, after OnUpdate()
     *      - Used for:
     *              - Rendering entities
     *              - Dynamic graphic properties
     */
    void OnRender() override;
};
