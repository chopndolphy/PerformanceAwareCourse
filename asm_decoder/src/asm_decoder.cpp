#include "Decoder.h"
#include "UserInterface.h"
#include "Application.h"

int main() {
    Decoder decoder;
    UserInterface userInterface;
    Application app(decoder, userInterface);

    app.Run();

    return 0;
}