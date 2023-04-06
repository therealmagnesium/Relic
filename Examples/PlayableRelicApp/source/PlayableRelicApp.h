#include <Relic.h>

// Make an app class that inherits from Relic::Application
class PlayableRelicApp : public Relic::Application
{
public:
    PlayableRelicApp(const Relic::ApplicationProperties& props);

    /* OnStart()
     *      - Called once, when the app is initialized
     *      - Used for initializing entities and other game objects
     */
    void OnStart() override;

    /* OnUpdate()
     *      - Called once per frame
     *      - Used for:
     *              - Handeling input
     *              - Collisions / physics
     *              - Movement
     */
    void OnUpdate() override;

    /* OnRender()
     *      - Called once per frame, after OnUpdate()
     *      - Used for:
     *              - Rendering enteties
     *              - Dynamic graphic properties
     */
    void OnRender() override;

private:
    // A helper function to handle player movement
    void HandleMovement();

    // A small helper function to spawn entities
    std::shared_ptr<Relic::Entity> SpawnEntity(Relic::Vector2 position, Relic::Vector2 velocity, float radius, int points, const sf::Color& fill, const sf::Color& outline);

private:
    //std::shared_ptr<Relic::EntityManager> m_entityManager;
    std::shared_ptr<Relic::Entity> m_player;
    std::shared_ptr<Relic::Entity> m_octogon;
    std::shared_ptr<Relic::Entity> m_square;
};
