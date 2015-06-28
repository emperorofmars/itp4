#include <bits/shared_ptr.h>
#include <src/scene/Node.h>
#include <src/overlay/Overlay.h>
#include "../EngineHelper.h"

class Menu {
public:
    Menu();
    ~Menu();

    std::shared_ptr <mgf::Node> root;
    std::shared_ptr <mgf::Node> actualScene;
    std::shared_ptr <mgf::Overlay> menuOverlay;

    void create(std::shared_ptr<EngineHelper>);

};