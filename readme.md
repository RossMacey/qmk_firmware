# This repo

I just wanted to save off my keymaps without merging them with the official repository (since I don't think there's much benefit for others).

## Usage from Windows

[This QMK page](https://docs.qmk.fm/#/newbs_getting_started) is good for getting started. I wrote a bunch of notes in my OneNote → Infrequent → Misc → GMMK 75.

-   Ensure QMK MSYS is up-to-date ([reference](https://docs.qmk.fm/#/newbs_getting_started?id=set-up-your-environment)). Almost every single confusing problem I had at first could have been solved by updating QMK MSYS. It seems to remember its installation directory, but I did end up with `E:\QMK_MSYS\QMK_MSYS` somehow despite that. 🤷‍♂️
-   MinGW64 stuff apparently shouldn't be needed with QMK MSYS, but I still copied `mingw64.exe` into the QMK MSYS folder and used that as my shell for all of the commands below. You can also just run the "QMK MSYS" shortcut, which appears to just be a shortcut to `ConEmu64.exe` + `bash.exe`: `E:\QMK_MSYS\conemu\ConEmu64.exe -NoSingle -NoUpdate -icon "E:\QMK_MSYS\icon.ico" -title "QMK MSYS" -run "E:\QMK_MSYS\usr\bin\bash.exe" -l -i -cur_console:m:""`
-   Set defaults for QMK so that you don't need to specify `-km` (keymap) or `kb` (keyboard) arguments. I only have the one QMK keyboard after all!
    -   `qmk config user.keyboard=gmmk/pro/ansi` or `qmk config user.keyboard=moonlander` or `qmk config user.keyboard=crkbd`
    -   `qmk config user.keymap=adam`
-   Clone this repo
-   `qmk setup -H /e/qmk_firmware/`
    -   `/e/qmk_firmware` represents `E:\qmk_firmware`, which is where I cloned the QMK repo. This'll save a bunch of space in your home directory.
-   `qmk flash -j 8`
    -   This compiles _and_ flashes; no need to run `qmk compile` on its own.
    -   `-j 8` is the thread count.
    -   You should see it print something like "INFO Compiling keymap with make -j 8 gmmk/pro/ansi:adam:flash" as the first line.
-   Press the RESET key on the keyboard (`fn+\` on the GMMK Pro) to enter bootloading. On the GMMK Pro _without_ QMK, the RESET sequence is to disconnect the keyboard and hold space+B before reconnecting.

## Changes to the GMMK Pro keymap

[Link to my keymap folder](./keyboards/gmmk/pro/ansi/keymaps/adam).

-   Semicolon - this is a "custom" layer-tap key to get into the `_NAV` layer (the "custom" part comes from treating all keys _after_ a semicolon as being modified regardless of whether the semicolon was still held).
-   Encoder
    -   Pressing it in pauses/plays media
    -   Modifier keys (code taken from [here](https://github.com/qmk/qmk_firmware/blob/d90897052243808863bcab3b07e16d5b6a0b08f0/keyboards/gmmk/pro/ansi/keymaps/jonavin/keymap.c#L124-L149))
        -   Shift: pgup/pgdown
        -   Ctrl: navigate by word
        -   Alt: change media track
        -   No mod: volume
-   The four-key cluster on the right side is X → Delete → Home → End. "X" is currently to change layers, but I'm not too tied to that.
-   Layers:
    -   Quick descriptions
        -   `_MAIN`: base layer, pink.
        -   `_NUMP`: numpad layer, green. From `_MAIN2`, press 7, 8, or 9 to enter. Press either semicolon or apostrophe to leave.
        -   `_NAV`: extra functionality (mostly for navigation, e.g. IJKL arrow keys).
        -   `_FUNC`: RGB+RESET layer, blue. Hold FN to use.

## Moonlander notes

[Link to my keymap folder](./keyboards/moonlander/keymaps/adam).

-   Default layer: rather than rely on Karabiner-Elements on macOS to remap modifier keys, I now rely on default layers to do this. `get_highest_layer` _always_ returns `_WIN_BASE` for some reason, so there's an extra check in there to see if the default layer is set to `_MAC_BASE`.
-   Moonlander LED codes (credit to [rtings](https://www.rtings.com/keyboard/reviews/zsa/moonlander) for the base picture):
    ![image](https://user-images.githubusercontent.com/7192897/133934938-95d21fd5-ec41-47c8-9d8a-0c7b1b327120.png)

## Corne notes

[Link to my keymap folder](./keyboards/crkbd/keymaps/adam).

-   See [this repo](https://github.com/Adam13531/crkbd/tree/choc-v3) for the choc v3 Corne that I made.
-   To reset the Corne, you can do any of the following (in order of easy → hard):
    -   Press the `RESET` key if you already have it mapped in QMK (my keymap _does_ have this mapped)
    -   Hold the Q or P key (depending on which half of the keyboard you're flashing) while plugging in the keyboard
    -   Bridge the `RST` and `GND` pins

## Helpful links

-   [How to detect layer changes](https://github.com/qmk/qmk_firmware/issues/2862#issuecomment-531015490). Note that `layer_state` is just a global with the current value ([reference](https://github.com/qmk/qmk_firmware/blob/9dea6f772077dc5c09daf40378e45884d29ab2e2/tmk_core/common/action_layer.c#L81)).
-   Configuring VSCode is probably a good idea ([reference](https://docs.qmk.fm/#/other_vscode?id=configuring-vs-code)).

## Troubleshooting

-   General troubles: try `qmk doctor` to detect issues and `qmk clean`
-   Linker issues: this could be due to having something in `rules.mk`; I once hit this when I had `COMBO_ENABLE = yes` in there, and removing it fixed everything.
-   If `KC_CAPS` is being sent as ctrl, then it's some random new bug that I encountered and didn't find an existing issue for. The workaround is to make `KC_CAPS` into a dual-function key. This only happens for me when the left half of the Corne is plugged in via USB.
