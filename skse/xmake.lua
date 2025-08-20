-- set minimum xmake version
set_xmakever("2.8.2")

includes("lib/commonlibsse-ng")

set_project("RfaD-Oil-Widget")
set_version("0.2.0-beta")
set_license("GPL-3.0")

set_arch("x64")

set_languages("c++23")
set_warnings("allextra")

set_policy("package.requires_lock", true)

add_rules("mode.release")
add_rules("plugin.vsxmake.autoupdate")

-- targets
target("RfaD-Oil-Widget")
    add_deps("commonlibsse-ng")

    add_rules("commonlibsse-ng.plugin", {
       name = "RfaD-Oil-Widget",
       author = "Amirust <discord: amirust>",
       description = "Oil Widget for RfaD using CommonLibSSE-NG and PrismaUI"
    })

    add_files("src/**.cpp")
    add_headerfiles("src/**.h")
    add_includedirs("src")
    set_pcxxheader("src/pch.h")