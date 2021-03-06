#pragma once

#include <MAE/Main.h>
#include <MAE/Core/UnorderedVector.h>

#include <GMLAPI/Stream.h>

#include <vector>

#define DLLEXPORT extern "C" __declspec (dllexport)

#define TRYBEG() try { do { } while (0)
#define TRYEND(ret) } catch (std::exception& ex) { error(ex.what()); return (ret); } do { } while (0)

extern Main* mamain;
extern std::vector<float> matStack;
extern UnorderedVector<Stream*> streams;
extern class Renderer* renderer;
extern class CFmod* mafmod;

void error(const char* msg);
