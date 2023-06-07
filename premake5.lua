workspace "RelicWorkspace"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

include "Relic"
include "Examples/Basic"
include "Examples/ShapeShooterz"
