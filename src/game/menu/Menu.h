#include <bits/shared_ptr.h>
#include <src/scene/Node.h>
#include <src/overlay/Overlay.h>

class Menu {
public:
    std::shared_ptr <mgf::Node> root;
    std::shared_ptr <mgf::Node> actualScene;
    std::shared_ptr <mgf::Overlay> menuOverlay;
private:
};