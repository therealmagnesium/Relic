#include "MainMenuScene.h"
#include "GameScene.h"

MainMenuScene::MainMenuScene(Application* app) :
    Scene(app)
{
    CreateBackground();
    SpawnLogo();
    SpawnStartText();
    SpawnAllEntities();
    SetupAndPlayAudio();
}

void MainMenuScene::OnUpdate()
{
    if (Input::IsKeyPressed(Key::Escape))
        m_app->Close();

    if (Input::IsKeyPressed(Key::Num2))
        m_app->ChangeScene("game", std::make_shared<GameScene>(m_app), true);

    RotateAllEntities();
}

void MainMenuScene::OnEnd()
{
    RL_INFO("Ending scene [{}]", m_app->GetCurrentScene());
    m_backgroundMusic->GetComponent<AudioSource>().audio.Stop();
}

void MainMenuScene::CreateBackground()
{
    std::shared_ptr<Entity> bg = m_entityManager.AddEntity("bg");
    bg->AddComponent<Transform>();
    bg->AddComponent<SpriteRenderer>(m_app->GetAssets()->GetTexture("main_menu_bg"));
}

void MainMenuScene::SetupAndPlayAudio()
{
    m_backgroundMusic = m_entityManager.AddEntity("music");
    m_backgroundMusic->AddComponent<AudioSource>(m_app->GetAssets()->GetMusicPath("menu"));
    m_backgroundMusic->GetComponent<AudioSource>().audio.SetStartOffset(0.f);
    m_backgroundMusic->GetComponent<AudioSource>().audio.SetLoop(true);
    m_backgroundMusic->GetComponent<AudioSource>().audio.Play();
}

void MainMenuScene::SpawnLogo()
{
    std::shared_ptr<Entity> logo = m_entityManager.AddEntity("menu_token");
    logo->AddComponent<Transform>(Vector2(m_app->GetWindowWidth()/2.f, 500.f));
    logo->AddComponent<SpriteRenderer>(m_app->GetAssets()->GetTexture("relic_logo"));
    auto& sr = logo->GetComponent<SpriteRenderer>().sprite;
    sr.SetOrigin(sr.GetSize().x/2.f, sr.GetSize().y/2.f);
    sr.SetScale(0.7f, 0.7f);
}

void MainMenuScene::SpawnStartText()
{
    std::shared_ptr<Entity> startText = m_entityManager.AddEntity("menu_token");
    startText->AddComponent<Transform>(Vector2(m_app->GetWindowWidth()/2.f, 
                m_app->GetWindowHeight()/1.5f));
    startText->AddComponent<Text>(m_app->GetAssets()->GetFont("main"), "Press 2 to play game", 40);
    auto& text = startText->GetComponent<Text>().text;
    text.SetOrigin(text.GetWidth()/2.f, text.GetHeight()/2.f);
}

void MainMenuScene::SpawnAllEntities()
{
    SpawnEntity(Vector2(400.f, 400.f));
    SpawnEntity(Vector2(m_app->GetWindowWidth() - 400.f, 400.f)); 
}
void MainMenuScene::SpawnEntity(const Vector2& pos)
{
    std::shared_ptr<Entity> entity = m_entityManager.AddEntity("entity");
    entity->AddComponent<Shape>(64.f);
    auto& shape = entity->GetComponent<Shape>().shape;
    shape.SetOutlineColor(0x0FA3B1FF);
    shape.SetOrigin(shape.GetRadius(), shape.GetRadius()); 
    entity->AddComponent<Transform>(pos);
}

void MainMenuScene::RotateAllEntities()
{
    for (auto& e : m_entityManager.GetEntities("entity"))
        e->GetComponent<Transform>().angle += 2.f;
}
