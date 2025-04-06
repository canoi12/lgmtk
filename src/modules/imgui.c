#include "lgmtk.h"
#include "lua_helper.h"

#include "common.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS 1
#include "cimgui.h"
#include "cimgui_impl.h"

typedef struct { const char* name; int value; } CImguiEnum;

const CImguiEnum l_ImGuiSelectableFlags[] = {
    {"None", 0},
    {"NoAutoClosePopups", 1 << 0},
    {"SpanAllColumns", 1 << 1},
    {"AllowDoubleClick", 1 << 2},
    {"Disabled", 1 << 3},
    {"AllowOverlap", 1 << 4},
    {"Highlight", 1 << 5},
{NULL, 0},
};
const CImguiEnum l_ImGuiMouseSource[] = {
    {"Mouse", 0},
    {"TouchScreen", 1},
    {"Pen", 2},
    {"COUNT", 3},
{NULL, 0},
};
const CImguiEnum l_ImGuiButtonFlagsPrivate[] = {
    {"PressedOnClick", 1 << 4},
    {"PressedOnClickRelease", 1 << 5},
    {"PressedOnClickReleaseAnywhere", 1 << 6},
    {"PressedOnRelease", 1 << 7},
    {"PressedOnDoubleClick", 1 << 8},
    {"PressedOnDragDropHold", 1 << 9},
    {"FlattenChildren", 1 << 11},
    {"AllowOverlap", 1 << 12},
    {"AlignTextBaseLine", 1 << 15},
    {"NoKeyModsAllowed", 1 << 16},
    {"NoHoldingActiveId", 1 << 17},
    {"NoNavFocus", 1 << 18},
    {"NoHoveredOnFocus", 1 << 19},
    {"NoSetKeyOwner", 1 << 20},
    {"NoTestKeyOwner", 1 << 21},
    {"PressedOnMask", ImGuiButtonFlags_PressedOnClick | ImGuiButtonFlags_PressedOnClickRelease | ImGuiButtonFlags_PressedOnClickReleaseAnywhere | ImGuiButtonFlags_PressedOnRelease | ImGuiButtonFlags_PressedOnDoubleClick | ImGuiButtonFlags_PressedOnDragDropHold},
    {"PressedOnDefault", ImGuiButtonFlags_PressedOnClickRelease},
{NULL, 0},
};
const CImguiEnum l_ImGuiTooltipFlags[] = {
    {"None", 0},
    {"OverridePrevious", 1 << 1},
{NULL, 0},
};
const CImguiEnum l_ImGuiDragDropFlags[] = {
    {"None", 0},
    {"SourceNoPreviewTooltip", 1 << 0},
    {"SourceNoDisableHover", 1 << 1},
    {"SourceNoHoldToOpenOthers", 1 << 2},
    {"SourceAllowNullID", 1 << 3},
    {"SourceExtern", 1 << 4},
    {"PayloadAutoExpire", 1 << 5},
    {"PayloadNoCrossContext", 1 << 6},
    {"PayloadNoCrossProcess", 1 << 7},
    {"AcceptBeforeDelivery", 1 << 10},
    {"AcceptNoDrawDefaultRect", 1 << 11},
    {"AcceptNoPreviewTooltip", 1 << 12},
    {"AcceptPeekOnly", ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect},
{NULL, 0},
};
const CImguiEnum l_ImGuiTableColumnFlags[] = {
    {"None", 0},
    {"Disabled", 1 << 0},
    {"DefaultHide", 1 << 1},
    {"DefaultSort", 1 << 2},
    {"WidthStretch", 1 << 3},
    {"WidthFixed", 1 << 4},
    {"NoResize", 1 << 5},
    {"NoReorder", 1 << 6},
    {"NoHide", 1 << 7},
    {"NoClip", 1 << 8},
    {"NoSort", 1 << 9},
    {"NoSortAscending", 1 << 10},
    {"NoSortDescending", 1 << 11},
    {"NoHeaderLabel", 1 << 12},
    {"NoHeaderWidth", 1 << 13},
    {"PreferSortAscending", 1 << 14},
    {"PreferSortDescending", 1 << 15},
    {"IndentEnable", 1 << 16},
    {"IndentDisable", 1 << 17},
    {"AngledHeader", 1 << 18},
    {"IsEnabled", 1 << 24},
    {"IsVisible", 1 << 25},
    {"IsSorted", 1 << 26},
    {"IsHovered", 1 << 27},
    {"WidthMask", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_WidthFixed},
    {"IndentMask", ImGuiTableColumnFlags_IndentEnable | ImGuiTableColumnFlags_IndentDisable},
    {"StatusMask", ImGuiTableColumnFlags_IsEnabled | ImGuiTableColumnFlags_IsVisible | ImGuiTableColumnFlags_IsSorted | ImGuiTableColumnFlags_IsHovered},
    {"NoDirectResize", 1 << 30},
{NULL, 0},
};
const CImguiEnum l_ImGuiPopupPositionPolicy[] = {
    {"Default", 0},
    {"ComboBox", 1},
    {"Tooltip", 2},
{NULL, 0},
};
const CImguiEnum l_ImGuiFocusRequestFlags[] = {
    {"None", 0},
    {"RestoreFocusedChild", 1 << 0},
    {"UnlessBelowModal", 1 << 1},
{NULL, 0},
};
const CImguiEnum l_ImGuiWindowRefreshFlags[] = {
    {"None", 0},
    {"TryToAvoidRefresh", 1 << 0},
    {"RefreshOnHover", 1 << 1},
    {"RefreshOnFocus", 1 << 2},
{NULL, 0},
};
const CImguiEnum l_ImGuiColorEditFlags[] = {
    {"None", 0},
    {"NoAlpha", 1 << 1},
    {"NoPicker", 1 << 2},
    {"NoOptions", 1 << 3},
    {"NoSmallPreview", 1 << 4},
    {"NoInputs", 1 << 5},
    {"NoTooltip", 1 << 6},
    {"NoLabel", 1 << 7},
    {"NoSidePreview", 1 << 8},
    {"NoDragDrop", 1 << 9},
    {"NoBorder", 1 << 10},
    {"AlphaOpaque", 1 << 11},
    {"AlphaNoBg", 1 << 12},
    {"AlphaPreviewHalf", 1 << 13},
    {"AlphaBar", 1 << 16},
    {"HDR", 1 << 19},
    {"DisplayRGB", 1 << 20},
    {"DisplayHSV", 1 << 21},
    {"DisplayHex", 1 << 22},
    {"Uint8", 1 << 23},
    {"Float", 1 << 24},
    {"PickerHueBar", 1 << 25},
    {"PickerHueWheel", 1 << 26},
    {"InputRGB", 1 << 27},
    {"InputHSV", 1 << 28},
    {"DefaultOptions", ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_PickerHueBar},
    {"AlphaMask", ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_AlphaOpaque | ImGuiColorEditFlags_AlphaNoBg | ImGuiColorEditFlags_AlphaPreviewHalf},
    {"DisplayMask", ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_DisplayHex},
    {"DataTypeMask", ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_Float},
    {"PickerMask", ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_PickerHueBar},
    {"InputMask", ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_InputHSV},
{NULL, 0},
};
const CImguiEnum l_ImGuiPopupFlags[] = {
    {"None", 0},
    {"MouseButtonLeft", 0},
    {"MouseButtonRight", 1},
    {"MouseButtonMiddle", 2},
    {"MouseButtonMask", 0x1F},
    {"MouseButtonDefault", 1},
    {"NoReopen", 1 << 5},
    {"NoOpenOverExistingPopup", 1 << 7},
    {"NoOpenOverItems", 1 << 8},
    {"AnyPopupId", 1 << 10},
    {"AnyPopupLevel", 1 << 11},
    {"AnyPopup", ImGuiPopupFlags_AnyPopupId | ImGuiPopupFlags_AnyPopupLevel},
{NULL, 0},
};
const CImguiEnum l_ImGuiSortDirection[] = {
    {"None", 0},
    {"Ascending", 1},
    {"Descending", 2},
{NULL, 0},
};
const CImguiEnum l_ImGuiItemFlagsPrivate[] = {
    {"Disabled", 1 << 10},
    {"ReadOnly", 1 << 11},
    {"MixedValue", 1 << 12},
    {"NoWindowHoverableCheck", 1 << 13},
    {"AllowOverlap", 1 << 14},
    {"NoNavDisableMouseHover", 1 << 15},
    {"NoMarkEdited", 1 << 16},
    {"Inputable", 1 << 20},
    {"HasSelectionUserData", 1 << 21},
    {"IsMultiSelect", 1 << 22},
    {"Default", ImGuiItemFlags_AutoClosePopups},
{NULL, 0},
};
const CImguiEnum l_ImDrawFlags[] = {
    {"None", 0},
    {"Closed", 1 << 0},
    {"RoundCornersTopLeft", 1 << 4},
    {"RoundCornersTopRight", 1 << 5},
    {"RoundCornersBottomLeft", 1 << 6},
    {"RoundCornersBottomRight", 1 << 7},
    {"RoundCornersNone", 1 << 8},
    {"RoundCornersTop", ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight},
    {"RoundCornersBottom", ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersBottomRight},
    {"RoundCornersLeft", ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersTopLeft},
    {"RoundCornersRight", ImDrawFlags_RoundCornersBottomRight | ImDrawFlags_RoundCornersTopRight},
    {"RoundCornersAll", ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight | ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersBottomRight},
    {"RoundCornersDefault", ImDrawFlags_RoundCornersAll},
    {"RoundCornersMask", ImDrawFlags_RoundCornersAll | ImDrawFlags_RoundCornersNone},
{NULL, 0},
};
const CImguiEnum l_ImGuiChildFlags[] = {
    {"None", 0},
    {"Borders", 1 << 0},
    {"AlwaysUseWindowPadding", 1 << 1},
    {"ResizeX", 1 << 2},
    {"ResizeY", 1 << 3},
    {"AutoResizeX", 1 << 4},
    {"AutoResizeY", 1 << 5},
    {"AlwaysAutoResize", 1 << 6},
    {"FrameStyle", 1 << 7},
    {"NavFlattened", 1 << 8},
{NULL, 0},
};
const CImguiEnum l_ImGuiKey[] = {
    {"None", 0},
    {"NamedKey", 512},
    {"Tab", 512},
    {"LeftArrow", 513},
    {"RightArrow", 514},
    {"UpArrow", 515},
    {"DownArrow", 516},
    {"PageUp", 517},
    {"PageDown", 518},
    {"Home", 519},
    {"End", 520},
    {"Insert", 521},
    {"Delete", 522},
    {"Backspace", 523},
    {"Space", 524},
    {"Enter", 525},
    {"Escape", 526},
    {"LeftCtrl", 527},
    {"LeftShift", 528},
    {"LeftAlt", 529},
    {"LeftSuper", 530},
    {"RightCtrl", 531},
    {"RightShift", 532},
    {"RightAlt", 533},
    {"RightSuper", 534},
    {"Menu", 535},
    {"0", 536},
    {"1", 537},
    {"2", 538},
    {"3", 539},
    {"4", 540},
    {"5", 541},
    {"6", 542},
    {"7", 543},
    {"8", 544},
    {"9", 545},
    {"A", 546},
    {"B", 547},
    {"C", 548},
    {"D", 549},
    {"E", 550},
    {"F", 551},
    {"G", 552},
    {"H", 553},
    {"I", 554},
    {"J", 555},
    {"K", 556},
    {"L", 557},
    {"M", 558},
    {"N", 559},
    {"O", 560},
    {"P", 561},
    {"Q", 562},
    {"R", 563},
    {"S", 564},
    {"T", 565},
    {"U", 566},
    {"V", 567},
    {"W", 568},
    {"X", 569},
    {"Y", 570},
    {"Z", 571},
    {"F1", 572},
    {"F2", 573},
    {"F3", 574},
    {"F4", 575},
    {"F5", 576},
    {"F6", 577},
    {"F7", 578},
    {"F8", 579},
    {"F9", 580},
    {"F10", 581},
    {"F11", 582},
    {"F12", 583},
    {"F13", 584},
    {"F14", 585},
    {"F15", 586},
    {"F16", 587},
    {"F17", 588},
    {"F18", 589},
    {"F19", 590},
    {"F20", 591},
    {"F21", 592},
    {"F22", 593},
    {"F23", 594},
    {"F24", 595},
    {"Apostrophe", 596},
    {"Comma", 597},
    {"Minus", 598},
    {"Period", 599},
    {"Slash", 600},
    {"Semicolon", 601},
    {"Equal", 602},
    {"LeftBracket", 603},
    {"Backslash", 604},
    {"RightBracket", 605},
    {"GraveAccent", 606},
    {"CapsLock", 607},
    {"ScrollLock", 608},
    {"NumLock", 609},
    {"PrintScreen", 610},
    {"Pause", 611},
    {"Keypad0", 612},
    {"Keypad1", 613},
    {"Keypad2", 614},
    {"Keypad3", 615},
    {"Keypad4", 616},
    {"Keypad5", 617},
    {"Keypad6", 618},
    {"Keypad7", 619},
    {"Keypad8", 620},
    {"Keypad9", 621},
    {"KeypadDecimal", 622},
    {"KeypadDivide", 623},
    {"KeypadMultiply", 624},
    {"KeypadSubtract", 625},
    {"KeypadAdd", 626},
    {"KeypadEnter", 627},
    {"KeypadEqual", 628},
    {"AppBack", 629},
    {"AppForward", 630},
    {"Oem102", 631},
    {"GamepadStart", 632},
    {"GamepadBack", 633},
    {"GamepadFaceLeft", 634},
    {"GamepadFaceRight", 635},
    {"GamepadFaceUp", 636},
    {"GamepadFaceDown", 637},
    {"GamepadDpadLeft", 638},
    {"GamepadDpadRight", 639},
    {"GamepadDpadUp", 640},
    {"GamepadDpadDown", 641},
    {"GamepadL1", 642},
    {"GamepadR1", 643},
    {"GamepadL2", 644},
    {"GamepadR2", 645},
    {"GamepadL3", 646},
    {"GamepadR3", 647},
    {"GamepadLStickLeft", 648},
    {"GamepadLStickRight", 649},
    {"GamepadLStickUp", 650},
    {"GamepadLStickDown", 651},
    {"GamepadRStickLeft", 652},
    {"GamepadRStickRight", 653},
    {"GamepadRStickUp", 654},
    {"GamepadRStickDown", 655},
    {"MouseLeft", 656},
    {"MouseRight", 657},
    {"MouseMiddle", 658},
    {"MouseX1", 659},
    {"MouseX2", 660},
    {"MouseWheelX", 661},
    {"MouseWheelY", 662},
    {"ReservedForModCtrl", 663},
    {"ReservedForModShift", 664},
    {"ReservedForModAlt", 665},
    {"ReservedForModSuper", 666},
    {"NamedKey", 667},
    {"None", 0},
    {"Ctrl", 1 << 12},
    {"Shift", 1 << 13},
    {"Alt", 1 << 14},
    {"Super", 1 << 15},
    {"Mask", 0xF000},
    {"NamedKey", ImGuiKey_NamedKey_END - ImGuiKey_NamedKey_BEGIN},
{NULL, 0},
};
const CImguiEnum l_ImGuiTableBgTarget[] = {
    {"None", 0},
    {"RowBg0", 1},
    {"RowBg1", 2},
    {"CellBg", 3},
{NULL, 0},
};
const CImguiEnum l_ImGuiPlotType[] = {
    {"Lines", 0},
    {"Histogram", 1},
{NULL, 0},
};
const CImguiEnum l_ImGuiDataAuthority[] = {
    {"Auto", 0},
    {"DockNode", 1},
    {"Window", 2},
{NULL, 0},
};
const CImguiEnum l_ImGuiNextWindowDataFlags[] = {
    {"None", 0},
    {"HasPos", 1 << 0},
    {"HasSize", 1 << 1},
    {"HasContentSize", 1 << 2},
    {"HasCollapsed", 1 << 3},
    {"HasSizeConstraint", 1 << 4},
    {"HasFocus", 1 << 5},
    {"HasBgAlpha", 1 << 6},
    {"HasScroll", 1 << 7},
    {"HasWindowFlags", 1 << 8},
    {"HasChildFlags", 1 << 9},
    {"HasRefreshPolicy", 1 << 10},
    {"HasViewport", 1 << 11},
    {"HasDock", 1 << 12},
    {"HasWindowClass", 1 << 13},
{NULL, 0},
};
const CImguiEnum l_ImGuiMultiSelectFlags[] = {
    {"None", 0},
    {"SingleSelect", 1 << 0},
    {"NoSelectAll", 1 << 1},
    {"NoRangeSelect", 1 << 2},
    {"NoAutoSelect", 1 << 3},
    {"NoAutoClear", 1 << 4},
    {"NoAutoClearOnReselect", 1 << 5},
    {"BoxSelect1d", 1 << 6},
    {"BoxSelect2d", 1 << 7},
    {"BoxSelectNoScroll", 1 << 8},
    {"ClearOnEscape", 1 << 9},
    {"ClearOnClickVoid", 1 << 10},
    {"ScopeWindow", 1 << 11},
    {"ScopeRect", 1 << 12},
    {"SelectOnClick", 1 << 13},
    {"SelectOnClickRelease", 1 << 14},
    {"NavWrapX", 1 << 16},
{NULL, 0},
};
const CImguiEnum l_ImGuiComboFlags[] = {
    {"None", 0},
    {"PopupAlignLeft", 1 << 0},
    {"HeightSmall", 1 << 1},
    {"HeightRegular", 1 << 2},
    {"HeightLarge", 1 << 3},
    {"HeightLargest", 1 << 4},
    {"NoArrowButton", 1 << 5},
    {"NoPreview", 1 << 6},
    {"WidthFitPreview", 1 << 7},
    {"HeightMask", ImGuiComboFlags_HeightSmall | ImGuiComboFlags_HeightRegular | ImGuiComboFlags_HeightLarge | ImGuiComboFlags_HeightLargest},
{NULL, 0},
};
const CImguiEnum l_ImGuiSliderFlagsPrivate[] = {
    {"Vertical", 1 << 20},
    {"ReadOnly", 1 << 21},
{NULL, 0},
};
const CImguiEnum l_ImGuiInputTextFlags[] = {
    {"None", 0},
    {"CharsDecimal", 1 << 0},
    {"CharsHexadecimal", 1 << 1},
    {"CharsScientific", 1 << 2},
    {"CharsUppercase", 1 << 3},
    {"CharsNoBlank", 1 << 4},
    {"AllowTabInput", 1 << 5},
    {"EnterReturnsTrue", 1 << 6},
    {"EscapeClearsAll", 1 << 7},
    {"CtrlEnterForNewLine", 1 << 8},
    {"ReadOnly", 1 << 9},
    {"Password", 1 << 10},
    {"AlwaysOverwrite", 1 << 11},
    {"AutoSelectAll", 1 << 12},
    {"ParseEmptyRefVal", 1 << 13},
    {"DisplayEmptyRefVal", 1 << 14},
    {"NoHorizontalScroll", 1 << 15},
    {"NoUndoRedo", 1 << 16},
    {"ElideLeft", 1 << 17},
    {"CallbackCompletion", 1 << 18},
    {"CallbackHistory", 1 << 19},
    {"CallbackAlways", 1 << 20},
    {"CallbackCharFilter", 1 << 21},
    {"CallbackResize", 1 << 22},
    {"CallbackEdit", 1 << 23},
{NULL, 0},
};
const CImguiEnum l_ImGuiContextHookType[] = {
    {"NewFramePre", 0},
    {"NewFramePost", 1},
    {"EndFramePre", 2},
    {"EndFramePost", 3},
    {"RenderPre", 4},
    {"RenderPost", 5},
    {"Shutdown", 6},
    {"PendingRemoval", 7},
{NULL, 0},
};
const CImguiEnum l_ImGuiTypingSelectFlags[] = {
    {"None", 0},
    {"AllowBackspace", 1 << 0},
    {"AllowSingleCharMode", 1 << 1},
{NULL, 0},
};
const CImguiEnum l_ImGuiOldColumnFlags[] = {
    {"None", 0},
    {"NoBorder", 1 << 0},
    {"NoResize", 1 << 1},
    {"NoPreserveWidths", 1 << 2},
    {"NoForceWithinWindow", 1 << 3},
    {"GrowParentContentsSize", 1 << 4},
{NULL, 0},
};
const CImguiEnum l_ImGuiInputTextFlagsPrivate[] = {
    {"Multiline", 1 << 26},
    {"MergedItem", 1 << 27},
    {"LocalizeDecimalPoint", 1 << 28},
{NULL, 0},
};
const CImguiEnum l_ImGuiCond[] = {
    {"None", 0},
    {"Always", 1 << 0},
    {"Once", 1 << 1},
    {"FirstUseEver", 1 << 2},
    {"Appearing", 1 << 3},
{NULL, 0},
};
const CImguiEnum l_ImGuiComboFlagsPrivate[] = {
    {"CustomPreview", 1 << 20},
{NULL, 0},
};
const CImguiEnum l_ImGuiSeparatorFlags[] = {
    {"None", 0},
    {"Horizontal", 1 << 0},
    {"Vertical", 1 << 1},
    {"SpanAllColumns", 1 << 2},
{NULL, 0},
};
const CImguiEnum l_ImGuiDebugLogFlags[] = {
    {"None", 0},
    {"EventError", 1 << 0},
    {"EventActiveId", 1 << 1},
    {"EventFocus", 1 << 2},
    {"EventPopup", 1 << 3},
    {"EventNav", 1 << 4},
    {"EventClipper", 1 << 5},
    {"EventSelection", 1 << 6},
    {"EventIO", 1 << 7},
    {"EventFont", 1 << 8},
    {"EventInputRouting", 1 << 9},
    {"EventDocking", 1 << 10},
    {"EventViewport", 1 << 11},
    {"EventMask", ImGuiDebugLogFlags_EventError | ImGuiDebugLogFlags_EventActiveId | ImGuiDebugLogFlags_EventFocus | ImGuiDebugLogFlags_EventPopup | ImGuiDebugLogFlags_EventNav | ImGuiDebugLogFlags_EventClipper | ImGuiDebugLogFlags_EventSelection | ImGuiDebugLogFlags_EventIO | ImGuiDebugLogFlags_EventFont | ImGuiDebugLogFlags_EventInputRouting | ImGuiDebugLogFlags_EventDocking | ImGuiDebugLogFlags_EventViewport},
    {"OutputToTTY", 1 << 20},
    {"OutputToTestEngine", 1 << 21},
{NULL, 0},
};
const CImguiEnum l_ImGuiDataType[] = {
    {"S8", 0},
    {"U8", 1},
    {"S16", 2},
    {"U16", 3},
    {"S32", 4},
    {"U32", 5},
    {"S64", 6},
    {"U64", 7},
    {"Float", 8},
    {"Double", 9},
    {"Bool", 10},
    {"String", 11},
    {"COUNT", 12},
{NULL, 0},
};
const CImguiEnum l_ImGuiHoveredFlags[] = {
    {"None", 0},
    {"ChildWindows", 1 << 0},
    {"RootWindow", 1 << 1},
    {"AnyWindow", 1 << 2},
    {"NoPopupHierarchy", 1 << 3},
    {"DockHierarchy", 1 << 4},
    {"AllowWhenBlockedByPopup", 1 << 5},
    {"AllowWhenBlockedByActiveItem", 1 << 7},
    {"AllowWhenOverlappedByItem", 1 << 8},
    {"AllowWhenOverlappedByWindow", 1 << 9},
    {"AllowWhenDisabled", 1 << 10},
    {"NoNavOverride", 1 << 11},
    {"AllowWhenOverlapped", ImGuiHoveredFlags_AllowWhenOverlappedByItem | ImGuiHoveredFlags_AllowWhenOverlappedByWindow},
    {"RectOnly", ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenOverlapped},
    {"RootAndChildWindows", ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_ChildWindows},
    {"ForTooltip", 1 << 12},
    {"Stationary", 1 << 13},
    {"DelayNone", 1 << 14},
    {"DelayShort", 1 << 15},
    {"DelayNormal", 1 << 16},
    {"NoSharedDelay", 1 << 17},
{NULL, 0},
};
const CImguiEnum l_ImFontAtlasFlags[] = {
    {"None", 0},
    {"NoPowerOfTwoHeight", 1 << 0},
    {"NoMouseCursors", 1 << 1},
    {"NoBakedLines", 1 << 2},
{NULL, 0},
};
const CImguiEnum l_ImGuiNavLayer[] = {
    {"Main", 0},
    {"Menu", 1},
    {"COUNT", 2},
{NULL, 0},
};
const CImguiEnum l_ImGuiTabBarFlagsPrivate[] = {
    {"DockNode", 1 << 20},
    {"IsFocused", 1 << 21},
    {"SaveSettings", 1 << 22},
{NULL, 0},
};
const CImguiEnum l_ImGuiTreeNodeFlags[] = {
    {"None", 0},
    {"Selected", 1 << 0},
    {"Framed", 1 << 1},
    {"AllowOverlap", 1 << 2},
    {"NoTreePushOnOpen", 1 << 3},
    {"NoAutoOpenOnLog", 1 << 4},
    {"DefaultOpen", 1 << 5},
    {"OpenOnDoubleClick", 1 << 6},
    {"OpenOnArrow", 1 << 7},
    {"Leaf", 1 << 8},
    {"Bullet", 1 << 9},
    {"FramePadding", 1 << 10},
    {"SpanAvailWidth", 1 << 11},
    {"SpanFullWidth", 1 << 12},
    {"SpanLabelWidth", 1 << 13},
    {"SpanAllColumns", 1 << 14},
    {"LabelSpanAllColumns", 1 << 15},
    {"NavLeftJumpsBackHere", 1 << 17},
    {"CollapsingHeader", ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_NoAutoOpenOnLog},
{NULL, 0},
};
const CImguiEnum l_ImGuiTabBarFlags[] = {
    {"None", 0},
    {"Reorderable", 1 << 0},
    {"AutoSelectNewTabs", 1 << 1},
    {"TabListPopupButton", 1 << 2},
    {"NoCloseWithMiddleMouseButton", 1 << 3},
    {"NoTabListScrollingButtons", 1 << 4},
    {"NoTooltip", 1 << 5},
    {"DrawSelectedOverline", 1 << 6},
    {"FittingPolicyResizeDown", 1 << 7},
    {"FittingPolicyScroll", 1 << 8},
    {"FittingPolicyMask", ImGuiTabBarFlags_FittingPolicyResizeDown | ImGuiTabBarFlags_FittingPolicyScroll},
    {"FittingPolicyDefault", ImGuiTabBarFlags_FittingPolicyResizeDown},
{NULL, 0},
};
const CImguiEnum l_ImGuiAxis[] = {
    {"None", -1},
    {"X", 0},
    {"Y", 1},
{NULL, 0},
};
const CImguiEnum l_ImGuiInputEventType[] = {
    {"None", 0},
    {"MousePos", 1},
    {"MouseWheel", 2},
    {"MouseButton", 3},
    {"MouseViewport", 4},
    {"Key", 5},
    {"Text", 6},
    {"Focus", 7},
    {"COUNT", 8},
{NULL, 0},
};
const CImguiEnum l_ImGuiScrollFlags[] = {
    {"None", 0},
    {"KeepVisibleEdgeX", 1 << 0},
    {"KeepVisibleEdgeY", 1 << 1},
    {"KeepVisibleCenterX", 1 << 2},
    {"KeepVisibleCenterY", 1 << 3},
    {"AlwaysCenterX", 1 << 4},
    {"AlwaysCenterY", 1 << 5},
    {"NoScrollParent", 1 << 6},
    {"MaskX", ImGuiScrollFlags_KeepVisibleEdgeX | ImGuiScrollFlags_KeepVisibleCenterX | ImGuiScrollFlags_AlwaysCenterX},
    {"MaskY", ImGuiScrollFlags_KeepVisibleEdgeY | ImGuiScrollFlags_KeepVisibleCenterY | ImGuiScrollFlags_AlwaysCenterY},
{NULL, 0},
};
const CImguiEnum l_ImGuiNextItemDataFlags[] = {
    {"None", 0},
    {"HasWidth", 1 << 0},
    {"HasOpen", 1 << 1},
    {"HasShortcut", 1 << 2},
    {"HasRefVal", 1 << 3},
    {"HasStorageID", 1 << 4},
{NULL, 0},
};
const CImguiEnum l_ImGuiStyleVar[] = {
    {"Alpha", 0},
    {"DisabledAlpha", 1},
    {"WindowPadding", 2},
    {"WindowRounding", 3},
    {"WindowBorderSize", 4},
    {"WindowMinSize", 5},
    {"WindowTitleAlign", 6},
    {"ChildRounding", 7},
    {"ChildBorderSize", 8},
    {"PopupRounding", 9},
    {"PopupBorderSize", 10},
    {"FramePadding", 11},
    {"FrameRounding", 12},
    {"FrameBorderSize", 13},
    {"ItemSpacing", 14},
    {"ItemInnerSpacing", 15},
    {"IndentSpacing", 16},
    {"CellPadding", 17},
    {"ScrollbarSize", 18},
    {"ScrollbarRounding", 19},
    {"GrabMinSize", 20},
    {"GrabRounding", 21},
    {"ImageBorderSize", 22},
    {"TabRounding", 23},
    {"TabBorderSize", 24},
    {"TabBarBorderSize", 25},
    {"TabBarOverlineSize", 26},
    {"TableAngledHeadersAngle", 27},
    {"TableAngledHeadersTextAlign", 28},
    {"ButtonTextAlign", 29},
    {"SelectableTextAlign", 30},
    {"SeparatorTextBorderSize", 31},
    {"SeparatorTextAlign", 32},
    {"SeparatorTextPadding", 33},
    {"DockingSeparatorSize", 34},
    {"COUNT", 35},
{NULL, 0},
};
const CImguiEnum l_ImGuiActivateFlags[] = {
    {"None", 0},
    {"PreferInput", 1 << 0},
    {"PreferTweak", 1 << 1},
    {"TryToPreserveState", 1 << 2},
    {"FromTabbing", 1 << 3},
    {"FromShortcut", 1 << 4},
{NULL, 0},
};
const CImguiEnum l_ImGuiSliderFlags[] = {
    {"None", 0},
    {"Logarithmic", 1 << 5},
    {"NoRoundToFormat", 1 << 6},
    {"NoInput", 1 << 7},
    {"WrapAround", 1 << 8},
    {"ClampOnInput", 1 << 9},
    {"ClampZeroRange", 1 << 10},
    {"NoSpeedTweaks", 1 << 11},
    {"AlwaysClamp", ImGuiSliderFlags_ClampOnInput | ImGuiSliderFlags_ClampZeroRange},
    {"InvalidMask", 0x7000000F},
{NULL, 0},
};
const CImguiEnum l_ImGuiItemStatusFlags[] = {
    {"None", 0},
    {"HoveredRect", 1 << 0},
    {"HasDisplayRect", 1 << 1},
    {"Edited", 1 << 2},
    {"ToggledSelection", 1 << 3},
    {"ToggledOpen", 1 << 4},
    {"HasDeactivated", 1 << 5},
    {"Deactivated", 1 << 6},
    {"HoveredWindow", 1 << 7},
    {"Visible", 1 << 8},
    {"HasClipRect", 1 << 9},
    {"HasShortcut", 1 << 10},
{NULL, 0},
};
const CImguiEnum l_ImGuiHoveredFlagsPrivate[] = {
    {"DelayMask", ImGuiHoveredFlags_DelayNone | ImGuiHoveredFlags_DelayShort | ImGuiHoveredFlags_DelayNormal | ImGuiHoveredFlags_NoSharedDelay},
    {"AllowedMaskForIsWindowHovered", ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_AnyWindow | ImGuiHoveredFlags_NoPopupHierarchy | ImGuiHoveredFlags_DockHierarchy | ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_ForTooltip | ImGuiHoveredFlags_Stationary},
    {"AllowedMaskForIsItemHovered", ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenOverlapped | ImGuiHoveredFlags_AllowWhenDisabled | ImGuiHoveredFlags_NoNavOverride | ImGuiHoveredFlags_ForTooltip | ImGuiHoveredFlags_Stationary | ImGuiHoveredFlags_DelayMask_},
{NULL, 0},
};
const CImguiEnum l_ImGuiLocKey[] = {
    {"VersionStr", 0},
    {"TableSizeOne", 1},
    {"TableSizeAllFit", 2},
    {"TableSizeAllDefault", 3},
    {"TableResetOrder", 4},
    {"WindowingMainMenuBar", 5},
    {"WindowingPopup", 6},
    {"WindowingUntitled", 7},
    {"OpenLink", 8},
    {"CopyLink", 9},
    {"DockingHideTabBar", 10},
    {"DockingHoldShiftToDock", 11},
    {"DockingDragToUndockOrMoveNode", 12},
    {"COUNT", 13},
{NULL, 0},
};
const CImguiEnum l_ImGuiItemFlags[] = {
    {"None", 0},
    {"NoTabStop", 1 << 0},
    {"NoNav", 1 << 1},
    {"NoNavDefaultFocus", 1 << 2},
    {"ButtonRepeat", 1 << 3},
    {"AutoClosePopups", 1 << 4},
    {"AllowDuplicateId", 1 << 5},
{NULL, 0},
};
const CImguiEnum l_ImGuiLogFlags[] = {
    {"None", 0},
    {"OutputTTY", 1 << 0},
    {"OutputFile", 1 << 1},
    {"OutputBuffer", 1 << 2},
    {"OutputClipboard", 1 << 3},
    {"OutputMask", ImGuiLogFlags_OutputTTY | ImGuiLogFlags_OutputFile | ImGuiLogFlags_OutputBuffer | ImGuiLogFlags_OutputClipboard},
{NULL, 0},
};
const CImguiEnum l_ImGuiInputFlags[] = {
    {"None", 0},
    {"Repeat", 1 << 0},
    {"RouteActive", 1 << 10},
    {"RouteFocused", 1 << 11},
    {"RouteGlobal", 1 << 12},
    {"RouteAlways", 1 << 13},
    {"RouteOverFocused", 1 << 14},
    {"RouteOverActive", 1 << 15},
    {"RouteUnlessBgFocused", 1 << 16},
    {"RouteFromRootWindow", 1 << 17},
    {"Tooltip", 1 << 18},
{NULL, 0},
};
const CImguiEnum l_ImGuiTableFlags[] = {
    {"None", 0},
    {"Resizable", 1 << 0},
    {"Reorderable", 1 << 1},
    {"Hideable", 1 << 2},
    {"Sortable", 1 << 3},
    {"NoSavedSettings", 1 << 4},
    {"ContextMenuInBody", 1 << 5},
    {"RowBg", 1 << 6},
    {"BordersInnerH", 1 << 7},
    {"BordersOuterH", 1 << 8},
    {"BordersInnerV", 1 << 9},
    {"BordersOuterV", 1 << 10},
    {"BordersH", ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersOuterH},
    {"BordersV", ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuterV},
    {"BordersInner", ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersInnerH},
    {"BordersOuter", ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersOuterH},
    {"Borders", ImGuiTableFlags_BordersInner | ImGuiTableFlags_BordersOuter},
    {"NoBordersInBody", 1 << 11},
    {"NoBordersInBodyUntilResize", 1 << 12},
    {"SizingFixedFit", 1 << 13},
    {"SizingFixedSame", 2 << 13},
    {"SizingStretchProp", 3 << 13},
    {"SizingStretchSame", 4 << 13},
    {"NoHostExtendX", 1 << 16},
    {"NoHostExtendY", 1 << 17},
    {"NoKeepColumnsVisible", 1 << 18},
    {"PreciseWidths", 1 << 19},
    {"NoClip", 1 << 20},
    {"PadOuterX", 1 << 21},
    {"NoPadOuterX", 1 << 22},
    {"NoPadInnerX", 1 << 23},
    {"ScrollX", 1 << 24},
    {"ScrollY", 1 << 25},
    {"SortMulti", 1 << 26},
    {"SortTristate", 1 << 27},
    {"HighlightHoveredColumn", 1 << 28},
    {"SizingMask", ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_SizingFixedSame | ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_SizingStretchSame},
{NULL, 0},
};
const CImguiEnum l_ImGuiButtonFlags[] = {
    {"None", 0},
    {"MouseButtonLeft", 1 << 0},
    {"MouseButtonRight", 1 << 1},
    {"MouseButtonMiddle", 1 << 2},
    {"MouseButtonMask", ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight | ImGuiButtonFlags_MouseButtonMiddle},
    {"EnableNav", 1 << 3},
{NULL, 0},
};
const CImguiEnum l_ImGuiNavMoveFlags[] = {
    {"None", 0},
    {"LoopX", 1 << 0},
    {"LoopY", 1 << 1},
    {"WrapX", 1 << 2},
    {"WrapY", 1 << 3},
    {"WrapMask", ImGuiNavMoveFlags_LoopX | ImGuiNavMoveFlags_LoopY | ImGuiNavMoveFlags_WrapX | ImGuiNavMoveFlags_WrapY},
    {"AllowCurrentNavId", 1 << 4},
    {"AlsoScoreVisibleSet", 1 << 5},
    {"ScrollToEdgeY", 1 << 6},
    {"Forwarded", 1 << 7},
    {"DebugNoResult", 1 << 8},
    {"FocusApi", 1 << 9},
    {"IsTabbing", 1 << 10},
    {"IsPageMove", 1 << 11},
    {"Activate", 1 << 12},
    {"NoSelect", 1 << 13},
    {"NoSetNavCursorVisible", 1 << 14},
    {"NoClearActiveId", 1 << 15},
{NULL, 0},
};
const CImguiEnum l_ImGuiCol[] = {
    {"Text", 0},
    {"TextDisabled", 1},
    {"WindowBg", 2},
    {"ChildBg", 3},
    {"PopupBg", 4},
    {"Border", 5},
    {"BorderShadow", 6},
    {"FrameBg", 7},
    {"FrameBgHovered", 8},
    {"FrameBgActive", 9},
    {"TitleBg", 10},
    {"TitleBgActive", 11},
    {"TitleBgCollapsed", 12},
    {"MenuBarBg", 13},
    {"ScrollbarBg", 14},
    {"ScrollbarGrab", 15},
    {"ScrollbarGrabHovered", 16},
    {"ScrollbarGrabActive", 17},
    {"CheckMark", 18},
    {"SliderGrab", 19},
    {"SliderGrabActive", 20},
    {"Button", 21},
    {"ButtonHovered", 22},
    {"ButtonActive", 23},
    {"Header", 24},
    {"HeaderHovered", 25},
    {"HeaderActive", 26},
    {"Separator", 27},
    {"SeparatorHovered", 28},
    {"SeparatorActive", 29},
    {"ResizeGrip", 30},
    {"ResizeGripHovered", 31},
    {"ResizeGripActive", 32},
    {"TabHovered", 33},
    {"Tab", 34},
    {"TabSelected", 35},
    {"TabSelectedOverline", 36},
    {"TabDimmed", 37},
    {"TabDimmedSelected", 38},
    {"TabDimmedSelectedOverline", 39},
    {"DockingPreview", 40},
    {"DockingEmptyBg", 41},
    {"PlotLines", 42},
    {"PlotLinesHovered", 43},
    {"PlotHistogram", 44},
    {"PlotHistogramHovered", 45},
    {"TableHeaderBg", 46},
    {"TableBorderStrong", 47},
    {"TableBorderLight", 48},
    {"TableRowBg", 49},
    {"TableRowBgAlt", 50},
    {"TextLink", 51},
    {"TextSelectedBg", 52},
    {"DragDropTarget", 53},
    {"NavCursor", 54},
    {"NavWindowingHighlight", 55},
    {"NavWindowingDimBg", 56},
    {"ModalWindowDimBg", 57},
    {"COUNT", 58},
{NULL, 0},
};
const CImguiEnum l_ImGuiDir[] = {
    {"None", -1},
    {"Left", 0},
    {"Right", 1},
    {"Up", 2},
    {"Down", 3},
    {"COUNT", 4},
{NULL, 0},
};
const CImguiEnum l_ImGuiLayoutType[] = {
    {"Horizontal", 0},
    {"Vertical", 1},
{NULL, 0},
};
const CImguiEnum l_ImGuiWindowFlags[] = {
    {"None", 0},
    {"NoTitleBar", 1 << 0},
    {"NoResize", 1 << 1},
    {"NoMove", 1 << 2},
    {"NoScrollbar", 1 << 3},
    {"NoScrollWithMouse", 1 << 4},
    {"NoCollapse", 1 << 5},
    {"AlwaysAutoResize", 1 << 6},
    {"NoBackground", 1 << 7},
    {"NoSavedSettings", 1 << 8},
    {"NoMouseInputs", 1 << 9},
    {"MenuBar", 1 << 10},
    {"HorizontalScrollbar", 1 << 11},
    {"NoFocusOnAppearing", 1 << 12},
    {"NoBringToFrontOnFocus", 1 << 13},
    {"AlwaysVerticalScrollbar", 1 << 14},
    {"AlwaysHorizontalScrollbar", 1<< 15},
    {"NoNavInputs", 1 << 16},
    {"NoNavFocus", 1 << 17},
    {"UnsavedDocument", 1 << 18},
    {"NoDocking", 1 << 19},
    {"NoNav", ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus},
    {"NoDecoration", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse},
    {"NoInputs", ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus},
    {"DockNodeHost", 1 << 23},
    {"ChildWindow", 1 << 24},
    {"Tooltip", 1 << 25},
    {"Popup", 1 << 26},
    {"Modal", 1 << 27},
    {"ChildMenu", 1 << 28},
{NULL, 0},
};
const CImguiEnum l_ImGuiFocusedFlags[] = {
    {"None", 0},
    {"ChildWindows", 1 << 0},
    {"RootWindow", 1 << 1},
    {"AnyWindow", 1 << 2},
    {"NoPopupHierarchy", 1 << 3},
    {"DockHierarchy", 1 << 4},
    {"RootAndChildWindows", ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_ChildWindows},
{NULL, 0},
};
const CImguiEnum l_ImGuiDockNodeFlags[] = {
    {"None", 0},
    {"KeepAliveOnly", 1 << 0},
    {"NoDockingOverCentralNode", 1 << 2},
    {"PassthruCentralNode", 1 << 3},
    {"NoDockingSplit", 1 << 4},
    {"NoResize", 1 << 5},
    {"AutoHideTabBar", 1 << 6},
    {"NoUndocking", 1 << 7},
{NULL, 0},
};
const CImguiEnum l_ImGuiDockNodeState[] = {
    {"Unknown", 0},
    {"HostWindowHiddenBecauseSingleWindow", 1},
    {"HostWindowHiddenBecauseWindowsAreResizing", 2},
    {"HostWindowVisible", 3},
{NULL, 0},
};
const CImguiEnum l_ImGuiSelectionRequestType[] = {
    {"None", 0},
    {"SetAll", 1},
    {"SetRange", 2},
{NULL, 0},
};
const CImguiEnum l_ImGuiTextFlags[] = {
    {"None", 0},
    {"NoWidthForLargeClippedText", 1 << 0},
{NULL, 0},
};
const CImguiEnum l_ImGuiInputFlagsPrivate[] = {
    {"RepeatRateDefault", 1 << 1},
    {"RepeatRateNavMove", 1 << 2},
    {"RepeatRateNavTweak", 1 << 3},
    {"RepeatUntilRelease", 1 << 4},
    {"RepeatUntilKeyModsChange", 1 << 5},
    {"RepeatUntilKeyModsChangeFromNone", 1 << 6},
    {"RepeatUntilOtherKeyPress", 1 << 7},
    {"LockThisFrame", 1 << 20},
    {"LockUntilRelease", 1 << 21},
    {"CondHovered", 1 << 22},
    {"CondActive", 1 << 23},
    {"CondDefault", ImGuiInputFlags_CondHovered | ImGuiInputFlags_CondActive},
    {"RepeatRateMask", ImGuiInputFlags_RepeatRateDefault | ImGuiInputFlags_RepeatRateNavMove | ImGuiInputFlags_RepeatRateNavTweak},
    {"RepeatUntilMask", ImGuiInputFlags_RepeatUntilRelease | ImGuiInputFlags_RepeatUntilKeyModsChange | ImGuiInputFlags_RepeatUntilKeyModsChangeFromNone | ImGuiInputFlags_RepeatUntilOtherKeyPress},
    {"RepeatMask", ImGuiInputFlags_Repeat | ImGuiInputFlags_RepeatRateMask_ | ImGuiInputFlags_RepeatUntilMask_},
    {"CondMask", ImGuiInputFlags_CondHovered | ImGuiInputFlags_CondActive},
    {"RouteTypeMask", ImGuiInputFlags_RouteActive | ImGuiInputFlags_RouteFocused | ImGuiInputFlags_RouteGlobal | ImGuiInputFlags_RouteAlways},
    {"RouteOptionsMask", ImGuiInputFlags_RouteOverFocused | ImGuiInputFlags_RouteOverActive | ImGuiInputFlags_RouteUnlessBgFocused | ImGuiInputFlags_RouteFromRootWindow},
    {"SupportedByIsKeyPressed", ImGuiInputFlags_RepeatMask_},
    {"SupportedByIsMouseClicked", ImGuiInputFlags_Repeat},
    {"SupportedByShortcut", ImGuiInputFlags_RepeatMask_ | ImGuiInputFlags_RouteTypeMask_ | ImGuiInputFlags_RouteOptionsMask_},
    {"SupportedBySetNextItemShortcut", ImGuiInputFlags_RepeatMask_ | ImGuiInputFlags_RouteTypeMask_ | ImGuiInputFlags_RouteOptionsMask_ | ImGuiInputFlags_Tooltip},
    {"SupportedBySetKeyOwner", ImGuiInputFlags_LockThisFrame | ImGuiInputFlags_LockUntilRelease},
    {"SupportedBySetItemKeyOwner", ImGuiInputFlags_SupportedBySetKeyOwner | ImGuiInputFlags_CondMask_},
{NULL, 0},
};
const CImguiEnum l_ImGuiMouseCursor[] = {
    {"None", -1},
    {"Arrow", 0},
    {"TextInput", 1},
    {"ResizeAll", 2},
    {"ResizeNS", 3},
    {"ResizeEW", 4},
    {"ResizeNESW", 5},
    {"ResizeNWSE", 6},
    {"Hand", 7},
    {"Wait", 8},
    {"Progress", 9},
    {"NotAllowed", 10},
    {"COUNT", 11},
{NULL, 0},
};
const CImguiEnum l_ImGuiFreeTypeBuilderFlags[] = {
    {"NoHinting", 1 << 0},
    {"NoAutoHint", 1 << 1},
    {"ForceAutoHint", 1 << 2},
    {"LightHinting", 1 << 3},
    {"MonoHinting", 1 << 4},
    {"Bold", 1 << 5},
    {"Oblique", 1 << 6},
    {"Monochrome", 1 << 7},
    {"LoadColor", 1 << 8},
    {"Bitmap", 1 << 9},
{NULL, 0},
};
const CImguiEnum l_ImGuiTreeNodeFlagsPrivate[] = {
    {"ClipLabelForTrailingButton", 1 << 28},
    {"UpsideDownArrow", 1 << 29},
    {"OpenOnMask", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow},
{NULL, 0},
};
const CImguiEnum l_ImGuiInputSource[] = {
    {"None", 0},
    {"Mouse", 1},
    {"Keyboard", 2},
    {"Gamepad", 3},
    {"COUNT", 4},
{NULL, 0},
};
const CImguiEnum l_ImGuiTableRowFlags[] = {
    {"None", 0},
    {"Headers", 1 << 0},
{NULL, 0},
};
const CImguiEnum l_ImGuiMouseButton[] = {
    {"Left", 0},
    {"Right", 1},
    {"Middle", 2},
    {"COUNT", 5},
{NULL, 0},
};
const CImguiEnum l_ImGuiViewportFlags[] = {
    {"None", 0},
    {"IsPlatformWindow", 1 << 0},
    {"IsPlatformMonitor", 1 << 1},
    {"OwnedByApp", 1 << 2},
    {"NoDecoration", 1 << 3},
    {"NoTaskBarIcon", 1 << 4},
    {"NoFocusOnAppearing", 1 << 5},
    {"NoFocusOnClick", 1 << 6},
    {"NoInputs", 1 << 7},
    {"NoRendererClear", 1 << 8},
    {"NoAutoMerge", 1 << 9},
    {"TopMost", 1 << 10},
    {"CanHostOtherWindows", 1 << 11},
    {"IsMinimized", 1 << 12},
    {"IsFocused", 1 << 13},
{NULL, 0},
};
const CImguiEnum l_ImGuiConfigFlags[] = {
    {"None", 0},
    {"NavEnableKeyboard", 1 << 0},
    {"NavEnableGamepad", 1 << 1},
    {"NoMouse", 1 << 4},
    {"NoMouseCursorChange", 1 << 5},
    {"NoKeyboard", 1 << 6},
    {"DockingEnable", 1 << 7},
    {"ViewportsEnable", 1 << 10},
    {"DpiEnableScaleViewports", 1 << 14},
    {"DpiEnableScaleFonts", 1 << 15},
    {"IsSRGB", 1 << 20},
    {"IsTouchScreen", 1 << 21},
{NULL, 0},
};
const CImguiEnum l_ImGuiNavRenderCursorFlags[] = {
    {"None", 0},
    {"Compact", 1 << 1},
    {"AlwaysDraw", 1 << 2},
    {"NoRounding", 1 << 3},
{NULL, 0},
};
const CImguiEnum l_ImGuiDataTypePrivate[] = {
    {"Pointer", ImGuiDataType_COUNT},
    {"ID", ImGuiDataType_COUNT+1},
{NULL, 0},
};
const CImguiEnum l_ImGuiSelectableFlagsPrivate[] = {
    {"NoHoldingActiveID", 1 << 20},
    {"SelectOnNav", 1 << 21},
    {"SelectOnClick", 1 << 22},
    {"SelectOnRelease", 1 << 23},
    {"SpanAvailWidth", 1 << 24},
    {"SetNavIdOnHover", 1 << 25},
    {"NoPadWithHalfSpacing", 1 << 26},
    {"NoSetKeyOwner", 1 << 27},
{NULL, 0},
};
const CImguiEnum l_ImDrawListFlags[] = {
    {"None", 0},
    {"AntiAliasedLines", 1 << 0},
    {"AntiAliasedLinesUseTex", 1 << 1},
    {"AntiAliasedFill", 1 << 2},
    {"AllowVtxOffset", 1 << 3},
{NULL, 0},
};
const CImguiEnum l_ImGuiDockNodeFlagsPrivate[] = {
    {"DockSpace", 1 << 10},
    {"CentralNode", 1 << 11},
    {"NoTabBar", 1 << 12},
    {"HiddenTabBar", 1 << 13},
    {"NoWindowMenuButton", 1 << 14},
    {"NoCloseButton", 1 << 15},
    {"NoResizeX", 1 << 16},
    {"NoResizeY", 1 << 17},
    {"DockedWindowsInFocusRoute", 1 << 18},
    {"NoDockingSplitOther", 1 << 19},
    {"NoDockingOverMe", 1 << 20},
    {"NoDockingOverOther", 1 << 21},
    {"NoDockingOverEmpty", 1 << 22},
    {"NoDocking", ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoDockingOverOther | ImGuiDockNodeFlags_NoDockingOverEmpty | ImGuiDockNodeFlags_NoDockingSplit | ImGuiDockNodeFlags_NoDockingSplitOther},
    {"SharedFlagsInheritMask", ~0},
    {"NoResizeFlagsMask", (int)ImGuiDockNodeFlags_NoResize | ImGuiDockNodeFlags_NoResizeX | ImGuiDockNodeFlags_NoResizeY},
    {"LocalFlagsTransferMask", (int)ImGuiDockNodeFlags_NoDockingSplit | ImGuiDockNodeFlags_NoResizeFlagsMask_ | (int)ImGuiDockNodeFlags_AutoHideTabBar | ImGuiDockNodeFlags_CentralNode | ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_HiddenTabBar | ImGuiDockNodeFlags_NoWindowMenuButton | ImGuiDockNodeFlags_NoCloseButton},
    {"SavedFlagsMask", ImGuiDockNodeFlags_NoResizeFlagsMask_ | ImGuiDockNodeFlags_DockSpace | ImGuiDockNodeFlags_CentralNode | ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_HiddenTabBar | ImGuiDockNodeFlags_NoWindowMenuButton | ImGuiDockNodeFlags_NoCloseButton},
{NULL, 0},
};
const CImguiEnum l_ImGuiBackendFlags[] = {
    {"None", 0},
    {"HasGamepad", 1 << 0},
    {"HasMouseCursors", 1 << 1},
    {"HasSetMousePos", 1 << 2},
    {"RendererHasVtxOffset", 1 << 3},
    {"PlatformHasViewports", 1 << 10},
    {"HasMouseHoveredViewport", 1 << 11},
    {"RendererHasViewports", 1 << 12},
{NULL, 0},
};
const CImguiEnum l_ImGuiTabItemFlags[] = {
    {"None", 0},
    {"UnsavedDocument", 1 << 0},
    {"SetSelected", 1 << 1},
    {"NoCloseWithMiddleMouseButton", 1 << 2},
    {"NoPushId", 1 << 3},
    {"NoTooltip", 1 << 4},
    {"NoReorder", 1 << 5},
    {"Leading", 1 << 6},
    {"Trailing", 1 << 7},
    {"NoAssumedClosure", 1 << 8},
{NULL, 0},
};
const CImguiEnum l_ImGuiWindowDockStyleCol[] = {
    {"Text", 0},
    {"TabHovered", 1},
    {"TabFocused", 2},
    {"TabSelected", 3},
    {"TabSelectedOverline", 4},
    {"TabDimmed", 5},
    {"TabDimmedSelected", 6},
    {"TabDimmedSelectedOverline", 7},
    {"COUNT", 8},
{NULL, 0},
};
const CImguiEnum l_ImGuiTabItemFlagsPrivate[] = {
    {"SectionMask", ImGuiTabItemFlags_Leading | ImGuiTabItemFlags_Trailing},
    {"NoCloseButton", 1 << 20},
    {"Button", 1 << 21},
    {"Invisible", 1 << 22},
    {"Unsorted", 1 << 23},
{NULL, 0},
};
static MODULE_FUNCTION(imgui, Render) {
    INIT_ARG();
    igRender();
    return 0;
}
static MODULE_FUNCTION(imgui, End) {
    INIT_ARG();
    igEnd();
    return 0;
}
static MODULE_FUNCTION(imgui, NewFrame) {
    INIT_ARG();
    igNewFrame();
    return 0;
}
static MODULE_FUNCTION(imgui, Text) {
    INIT_ARG();
    CHECK_STRING(fmt);
    igText(fmt);
    return 0;
}
static MODULE_FUNCTION(imgui, GetDrawData) {
    INIT_ARG();
    ImDrawData* res = igGetDrawData();
    lua_pushlightuserdata(L, res);
    return 1;
}
static MODULE_FUNCTION(imgui, StyleColorsDark) {
    INIT_ARG();
    ImGuiStyle* dst = (ImGuiStyle*)lua_touserdata(L, arg++);
    igStyleColorsDark(dst);
    return 0;
}
static MODULE_FUNCTION(imgui, ShowDemoWindow) {
    INIT_ARG();
    OPT_BOOLEAN(p_open, NULL);
    igShowDemoWindow(&p_open);
    lua_pushboolean(L, p_open);
    return 1;
}
static MODULE_FUNCTION(imgui, DestroyContext) {
    INIT_ARG();
    ImGuiContext* ctx = (ImGuiContext*)lua_touserdata(L, arg++);
    igDestroyContext(ctx);
    return 0;
}
static MODULE_FUNCTION(imgui, Begin) {
    INIT_ARG();
    CHECK_STRING(name);
    OPT_BOOLEAN(p_open, NULL);
    OPT_INTEGER(flags, 0);
    bool res = igBegin(name,&p_open,flags);
    lua_pushboolean(L, res);
    lua_pushboolean(L, p_open);
    return 2;
}
static MODULE_FUNCTION(imgui, CreateContext) {
    INIT_ARG();
    ImFontAtlas* shared_font_atlas = (ImFontAtlas*)lua_touserdata(L, arg++);
    ImGuiContext* res = igCreateContext(shared_font_atlas);
    lua_pushlightuserdata(L, res);
    return 1;
}
static MODULE_FUNCTION(imgui, ImplSDL2_InitForSDLRenderer) {
    INIT_ARG();
    SDL_Window* win = (SDL_Window*)lua_touserdata(L, arg++);
    SDL_Renderer* ren = (SDL_Renderer*)lua_touserdata(L, arg++);
    ImGui_ImplSDL2_InitForSDLRenderer(win, ren);
    return 0;
}
static MODULE_FUNCTION(imgui, ImplSDLRenderer2_Init) {
    INIT_ARG();
    SDL_Renderer* ren = (SDL_Renderer*)lua_touserdata(L, arg++);
    ImGui_ImplSDLRenderer2_Init(ren);
    return 0;
}
static MODULE_FUNCTION(imgui, ImplSDLRenderer2_Shutdown) {
    INIT_ARG();
    ImGui_ImplSDLRenderer2_Shutdown();
    return 0;
}
static MODULE_FUNCTION(imgui, ImplSDL2_Shutdown) {
    INIT_ARG();
    ImGui_ImplSDL2_Shutdown();
    return 0;
}
static MODULE_FUNCTION(imgui, ImplSDLRenderer2_NewFrame) {
    INIT_ARG();
    ImGui_ImplSDLRenderer2_NewFrame();
    return 0;
}
static MODULE_FUNCTION(imgui, ImplSDL2_NewFrame) {
    INIT_ARG();
    ImGui_ImplSDL2_NewFrame();
    return 0;
}
static MODULE_FUNCTION(imgui, ImplSDL2_ProcessEvent) {
    INIT_ARG();
    SDL_Event* ev = (SDL_Event*)lua_touserdata(L, arg++);
    ImGui_ImplSDL2_ProcessEvent(ev);
    return 0;
}
static MODULE_FUNCTION(imgui, ImplSDLRenderer2_RenderDrawData) {
    INIT_ARG();
    ImDrawData* data = (ImDrawData*)lua_touserdata(L, arg++);
    SDL_Renderer* ren = (SDL_Renderer*)lua_touserdata(L, arg++);
    ImGui_ImplSDLRenderer2_RenderDrawData(data, ren);
    return 0;
}
const luaL_Reg _func_regs[] = {
    REG_FIELD(imgui, Render),
    REG_FIELD(imgui, End),
    REG_FIELD(imgui, NewFrame),
    REG_FIELD(imgui, Text),
    REG_FIELD(imgui, GetDrawData),
    REG_FIELD(imgui, StyleColorsDark),
    REG_FIELD(imgui, ShowDemoWindow),
    REG_FIELD(imgui, DestroyContext),
    REG_FIELD(imgui, Begin),
    REG_FIELD(imgui, CreateContext),
    REG_FIELD(imgui, ImplSDL2_InitForSDLRenderer),
    REG_FIELD(imgui, ImplSDLRenderer2_Init),
    REG_FIELD(imgui, ImplSDLRenderer2_Shutdown),
    REG_FIELD(imgui, ImplSDL2_Shutdown),
    REG_FIELD(imgui, ImplSDLRenderer2_NewFrame),
    REG_FIELD(imgui, ImplSDL2_NewFrame),
    REG_FIELD(imgui, ImplSDL2_ProcessEvent),
    REG_FIELD(imgui, ImplSDLRenderer2_RenderDrawData),
    {NULL, NULL}
};
int luaopen_imgui(lua_State* L) {
    luaL_newlib(L, _func_regs);
lua_newtable(L);
for (int i = 0; l_ImGuiSelectableFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiSelectableFlags[i].value);
    lua_setfield(L, -2, l_ImGuiSelectableFlags[i].name);
}
lua_setfield(L, -2, "ImGuiSelectableFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiMouseSource[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiMouseSource[i].value);
    lua_setfield(L, -2, l_ImGuiMouseSource[i].name);
}
lua_setfield(L, -2, "ImGuiMouseSource");
lua_newtable(L);
for (int i = 0; l_ImGuiButtonFlagsPrivate[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiButtonFlagsPrivate[i].value);
    lua_setfield(L, -2, l_ImGuiButtonFlagsPrivate[i].name);
}
lua_setfield(L, -2, "ImGuiButtonFlagsPrivate");
lua_newtable(L);
for (int i = 0; l_ImGuiTooltipFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiTooltipFlags[i].value);
    lua_setfield(L, -2, l_ImGuiTooltipFlags[i].name);
}
lua_setfield(L, -2, "ImGuiTooltipFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiDragDropFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiDragDropFlags[i].value);
    lua_setfield(L, -2, l_ImGuiDragDropFlags[i].name);
}
lua_setfield(L, -2, "ImGuiDragDropFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiTableColumnFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiTableColumnFlags[i].value);
    lua_setfield(L, -2, l_ImGuiTableColumnFlags[i].name);
}
lua_setfield(L, -2, "ImGuiTableColumnFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiPopupPositionPolicy[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiPopupPositionPolicy[i].value);
    lua_setfield(L, -2, l_ImGuiPopupPositionPolicy[i].name);
}
lua_setfield(L, -2, "ImGuiPopupPositionPolicy");
lua_newtable(L);
for (int i = 0; l_ImGuiFocusRequestFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiFocusRequestFlags[i].value);
    lua_setfield(L, -2, l_ImGuiFocusRequestFlags[i].name);
}
lua_setfield(L, -2, "ImGuiFocusRequestFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiWindowRefreshFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiWindowRefreshFlags[i].value);
    lua_setfield(L, -2, l_ImGuiWindowRefreshFlags[i].name);
}
lua_setfield(L, -2, "ImGuiWindowRefreshFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiColorEditFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiColorEditFlags[i].value);
    lua_setfield(L, -2, l_ImGuiColorEditFlags[i].name);
}
lua_setfield(L, -2, "ImGuiColorEditFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiPopupFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiPopupFlags[i].value);
    lua_setfield(L, -2, l_ImGuiPopupFlags[i].name);
}
lua_setfield(L, -2, "ImGuiPopupFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiSortDirection[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiSortDirection[i].value);
    lua_setfield(L, -2, l_ImGuiSortDirection[i].name);
}
lua_setfield(L, -2, "ImGuiSortDirection");
lua_newtable(L);
for (int i = 0; l_ImGuiItemFlagsPrivate[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiItemFlagsPrivate[i].value);
    lua_setfield(L, -2, l_ImGuiItemFlagsPrivate[i].name);
}
lua_setfield(L, -2, "ImGuiItemFlagsPrivate");
lua_newtable(L);
for (int i = 0; l_ImDrawFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImDrawFlags[i].value);
    lua_setfield(L, -2, l_ImDrawFlags[i].name);
}
lua_setfield(L, -2, "ImDrawFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiChildFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiChildFlags[i].value);
    lua_setfield(L, -2, l_ImGuiChildFlags[i].name);
}
lua_setfield(L, -2, "ImGuiChildFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiKey[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiKey[i].value);
    lua_setfield(L, -2, l_ImGuiKey[i].name);
}
lua_setfield(L, -2, "ImGuiKey");
lua_newtable(L);
for (int i = 0; l_ImGuiTableBgTarget[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiTableBgTarget[i].value);
    lua_setfield(L, -2, l_ImGuiTableBgTarget[i].name);
}
lua_setfield(L, -2, "ImGuiTableBgTarget");
lua_newtable(L);
for (int i = 0; l_ImGuiPlotType[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiPlotType[i].value);
    lua_setfield(L, -2, l_ImGuiPlotType[i].name);
}
lua_setfield(L, -2, "ImGuiPlotType");
lua_newtable(L);
for (int i = 0; l_ImGuiDataAuthority[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiDataAuthority[i].value);
    lua_setfield(L, -2, l_ImGuiDataAuthority[i].name);
}
lua_setfield(L, -2, "ImGuiDataAuthority");
lua_newtable(L);
for (int i = 0; l_ImGuiNextWindowDataFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiNextWindowDataFlags[i].value);
    lua_setfield(L, -2, l_ImGuiNextWindowDataFlags[i].name);
}
lua_setfield(L, -2, "ImGuiNextWindowDataFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiMultiSelectFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiMultiSelectFlags[i].value);
    lua_setfield(L, -2, l_ImGuiMultiSelectFlags[i].name);
}
lua_setfield(L, -2, "ImGuiMultiSelectFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiComboFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiComboFlags[i].value);
    lua_setfield(L, -2, l_ImGuiComboFlags[i].name);
}
lua_setfield(L, -2, "ImGuiComboFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiSliderFlagsPrivate[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiSliderFlagsPrivate[i].value);
    lua_setfield(L, -2, l_ImGuiSliderFlagsPrivate[i].name);
}
lua_setfield(L, -2, "ImGuiSliderFlagsPrivate");
lua_newtable(L);
for (int i = 0; l_ImGuiInputTextFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiInputTextFlags[i].value);
    lua_setfield(L, -2, l_ImGuiInputTextFlags[i].name);
}
lua_setfield(L, -2, "ImGuiInputTextFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiContextHookType[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiContextHookType[i].value);
    lua_setfield(L, -2, l_ImGuiContextHookType[i].name);
}
lua_setfield(L, -2, "ImGuiContextHookType");
lua_newtable(L);
for (int i = 0; l_ImGuiTypingSelectFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiTypingSelectFlags[i].value);
    lua_setfield(L, -2, l_ImGuiTypingSelectFlags[i].name);
}
lua_setfield(L, -2, "ImGuiTypingSelectFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiOldColumnFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiOldColumnFlags[i].value);
    lua_setfield(L, -2, l_ImGuiOldColumnFlags[i].name);
}
lua_setfield(L, -2, "ImGuiOldColumnFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiInputTextFlagsPrivate[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiInputTextFlagsPrivate[i].value);
    lua_setfield(L, -2, l_ImGuiInputTextFlagsPrivate[i].name);
}
lua_setfield(L, -2, "ImGuiInputTextFlagsPrivate");
lua_newtable(L);
for (int i = 0; l_ImGuiCond[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiCond[i].value);
    lua_setfield(L, -2, l_ImGuiCond[i].name);
}
lua_setfield(L, -2, "ImGuiCond");
lua_newtable(L);
for (int i = 0; l_ImGuiComboFlagsPrivate[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiComboFlagsPrivate[i].value);
    lua_setfield(L, -2, l_ImGuiComboFlagsPrivate[i].name);
}
lua_setfield(L, -2, "ImGuiComboFlagsPrivate");
lua_newtable(L);
for (int i = 0; l_ImGuiSeparatorFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiSeparatorFlags[i].value);
    lua_setfield(L, -2, l_ImGuiSeparatorFlags[i].name);
}
lua_setfield(L, -2, "ImGuiSeparatorFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiDebugLogFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiDebugLogFlags[i].value);
    lua_setfield(L, -2, l_ImGuiDebugLogFlags[i].name);
}
lua_setfield(L, -2, "ImGuiDebugLogFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiDataType[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiDataType[i].value);
    lua_setfield(L, -2, l_ImGuiDataType[i].name);
}
lua_setfield(L, -2, "ImGuiDataType");
lua_newtable(L);
for (int i = 0; l_ImGuiHoveredFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiHoveredFlags[i].value);
    lua_setfield(L, -2, l_ImGuiHoveredFlags[i].name);
}
lua_setfield(L, -2, "ImGuiHoveredFlags");
lua_newtable(L);
for (int i = 0; l_ImFontAtlasFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImFontAtlasFlags[i].value);
    lua_setfield(L, -2, l_ImFontAtlasFlags[i].name);
}
lua_setfield(L, -2, "ImFontAtlasFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiNavLayer[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiNavLayer[i].value);
    lua_setfield(L, -2, l_ImGuiNavLayer[i].name);
}
lua_setfield(L, -2, "ImGuiNavLayer");
lua_newtable(L);
for (int i = 0; l_ImGuiTabBarFlagsPrivate[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiTabBarFlagsPrivate[i].value);
    lua_setfield(L, -2, l_ImGuiTabBarFlagsPrivate[i].name);
}
lua_setfield(L, -2, "ImGuiTabBarFlagsPrivate");
lua_newtable(L);
for (int i = 0; l_ImGuiTreeNodeFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiTreeNodeFlags[i].value);
    lua_setfield(L, -2, l_ImGuiTreeNodeFlags[i].name);
}
lua_setfield(L, -2, "ImGuiTreeNodeFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiTabBarFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiTabBarFlags[i].value);
    lua_setfield(L, -2, l_ImGuiTabBarFlags[i].name);
}
lua_setfield(L, -2, "ImGuiTabBarFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiAxis[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiAxis[i].value);
    lua_setfield(L, -2, l_ImGuiAxis[i].name);
}
lua_setfield(L, -2, "ImGuiAxis");
lua_newtable(L);
for (int i = 0; l_ImGuiInputEventType[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiInputEventType[i].value);
    lua_setfield(L, -2, l_ImGuiInputEventType[i].name);
}
lua_setfield(L, -2, "ImGuiInputEventType");
lua_newtable(L);
for (int i = 0; l_ImGuiScrollFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiScrollFlags[i].value);
    lua_setfield(L, -2, l_ImGuiScrollFlags[i].name);
}
lua_setfield(L, -2, "ImGuiScrollFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiNextItemDataFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiNextItemDataFlags[i].value);
    lua_setfield(L, -2, l_ImGuiNextItemDataFlags[i].name);
}
lua_setfield(L, -2, "ImGuiNextItemDataFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiStyleVar[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiStyleVar[i].value);
    lua_setfield(L, -2, l_ImGuiStyleVar[i].name);
}
lua_setfield(L, -2, "ImGuiStyleVar");
lua_newtable(L);
for (int i = 0; l_ImGuiActivateFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiActivateFlags[i].value);
    lua_setfield(L, -2, l_ImGuiActivateFlags[i].name);
}
lua_setfield(L, -2, "ImGuiActivateFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiSliderFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiSliderFlags[i].value);
    lua_setfield(L, -2, l_ImGuiSliderFlags[i].name);
}
lua_setfield(L, -2, "ImGuiSliderFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiItemStatusFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiItemStatusFlags[i].value);
    lua_setfield(L, -2, l_ImGuiItemStatusFlags[i].name);
}
lua_setfield(L, -2, "ImGuiItemStatusFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiHoveredFlagsPrivate[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiHoveredFlagsPrivate[i].value);
    lua_setfield(L, -2, l_ImGuiHoveredFlagsPrivate[i].name);
}
lua_setfield(L, -2, "ImGuiHoveredFlagsPrivate");
lua_newtable(L);
for (int i = 0; l_ImGuiLocKey[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiLocKey[i].value);
    lua_setfield(L, -2, l_ImGuiLocKey[i].name);
}
lua_setfield(L, -2, "ImGuiLocKey");
lua_newtable(L);
for (int i = 0; l_ImGuiItemFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiItemFlags[i].value);
    lua_setfield(L, -2, l_ImGuiItemFlags[i].name);
}
lua_setfield(L, -2, "ImGuiItemFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiLogFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiLogFlags[i].value);
    lua_setfield(L, -2, l_ImGuiLogFlags[i].name);
}
lua_setfield(L, -2, "ImGuiLogFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiInputFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiInputFlags[i].value);
    lua_setfield(L, -2, l_ImGuiInputFlags[i].name);
}
lua_setfield(L, -2, "ImGuiInputFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiTableFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiTableFlags[i].value);
    lua_setfield(L, -2, l_ImGuiTableFlags[i].name);
}
lua_setfield(L, -2, "ImGuiTableFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiButtonFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiButtonFlags[i].value);
    lua_setfield(L, -2, l_ImGuiButtonFlags[i].name);
}
lua_setfield(L, -2, "ImGuiButtonFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiNavMoveFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiNavMoveFlags[i].value);
    lua_setfield(L, -2, l_ImGuiNavMoveFlags[i].name);
}
lua_setfield(L, -2, "ImGuiNavMoveFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiCol[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiCol[i].value);
    lua_setfield(L, -2, l_ImGuiCol[i].name);
}
lua_setfield(L, -2, "ImGuiCol");
lua_newtable(L);
for (int i = 0; l_ImGuiDir[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiDir[i].value);
    lua_setfield(L, -2, l_ImGuiDir[i].name);
}
lua_setfield(L, -2, "ImGuiDir");
lua_newtable(L);
for (int i = 0; l_ImGuiLayoutType[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiLayoutType[i].value);
    lua_setfield(L, -2, l_ImGuiLayoutType[i].name);
}
lua_setfield(L, -2, "ImGuiLayoutType");
lua_newtable(L);
for (int i = 0; l_ImGuiWindowFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiWindowFlags[i].value);
    lua_setfield(L, -2, l_ImGuiWindowFlags[i].name);
}
lua_setfield(L, -2, "ImGuiWindowFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiFocusedFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiFocusedFlags[i].value);
    lua_setfield(L, -2, l_ImGuiFocusedFlags[i].name);
}
lua_setfield(L, -2, "ImGuiFocusedFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiDockNodeFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiDockNodeFlags[i].value);
    lua_setfield(L, -2, l_ImGuiDockNodeFlags[i].name);
}
lua_setfield(L, -2, "ImGuiDockNodeFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiDockNodeState[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiDockNodeState[i].value);
    lua_setfield(L, -2, l_ImGuiDockNodeState[i].name);
}
lua_setfield(L, -2, "ImGuiDockNodeState");
lua_newtable(L);
for (int i = 0; l_ImGuiSelectionRequestType[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiSelectionRequestType[i].value);
    lua_setfield(L, -2, l_ImGuiSelectionRequestType[i].name);
}
lua_setfield(L, -2, "ImGuiSelectionRequestType");
lua_newtable(L);
for (int i = 0; l_ImGuiTextFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiTextFlags[i].value);
    lua_setfield(L, -2, l_ImGuiTextFlags[i].name);
}
lua_setfield(L, -2, "ImGuiTextFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiInputFlagsPrivate[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiInputFlagsPrivate[i].value);
    lua_setfield(L, -2, l_ImGuiInputFlagsPrivate[i].name);
}
lua_setfield(L, -2, "ImGuiInputFlagsPrivate");
lua_newtable(L);
for (int i = 0; l_ImGuiMouseCursor[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiMouseCursor[i].value);
    lua_setfield(L, -2, l_ImGuiMouseCursor[i].name);
}
lua_setfield(L, -2, "ImGuiMouseCursor");
lua_newtable(L);
for (int i = 0; l_ImGuiFreeTypeBuilderFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiFreeTypeBuilderFlags[i].value);
    lua_setfield(L, -2, l_ImGuiFreeTypeBuilderFlags[i].name);
}
lua_setfield(L, -2, "ImGuiFreeTypeBuilderFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiTreeNodeFlagsPrivate[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiTreeNodeFlagsPrivate[i].value);
    lua_setfield(L, -2, l_ImGuiTreeNodeFlagsPrivate[i].name);
}
lua_setfield(L, -2, "ImGuiTreeNodeFlagsPrivate");
lua_newtable(L);
for (int i = 0; l_ImGuiInputSource[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiInputSource[i].value);
    lua_setfield(L, -2, l_ImGuiInputSource[i].name);
}
lua_setfield(L, -2, "ImGuiInputSource");
lua_newtable(L);
for (int i = 0; l_ImGuiTableRowFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiTableRowFlags[i].value);
    lua_setfield(L, -2, l_ImGuiTableRowFlags[i].name);
}
lua_setfield(L, -2, "ImGuiTableRowFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiMouseButton[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiMouseButton[i].value);
    lua_setfield(L, -2, l_ImGuiMouseButton[i].name);
}
lua_setfield(L, -2, "ImGuiMouseButton");
lua_newtable(L);
for (int i = 0; l_ImGuiViewportFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiViewportFlags[i].value);
    lua_setfield(L, -2, l_ImGuiViewportFlags[i].name);
}
lua_setfield(L, -2, "ImGuiViewportFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiConfigFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiConfigFlags[i].value);
    lua_setfield(L, -2, l_ImGuiConfigFlags[i].name);
}
lua_setfield(L, -2, "ImGuiConfigFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiNavRenderCursorFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiNavRenderCursorFlags[i].value);
    lua_setfield(L, -2, l_ImGuiNavRenderCursorFlags[i].name);
}
lua_setfield(L, -2, "ImGuiNavRenderCursorFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiDataTypePrivate[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiDataTypePrivate[i].value);
    lua_setfield(L, -2, l_ImGuiDataTypePrivate[i].name);
}
lua_setfield(L, -2, "ImGuiDataTypePrivate");
lua_newtable(L);
for (int i = 0; l_ImGuiSelectableFlagsPrivate[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiSelectableFlagsPrivate[i].value);
    lua_setfield(L, -2, l_ImGuiSelectableFlagsPrivate[i].name);
}
lua_setfield(L, -2, "ImGuiSelectableFlagsPrivate");
lua_newtable(L);
for (int i = 0; l_ImDrawListFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImDrawListFlags[i].value);
    lua_setfield(L, -2, l_ImDrawListFlags[i].name);
}
lua_setfield(L, -2, "ImDrawListFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiDockNodeFlagsPrivate[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiDockNodeFlagsPrivate[i].value);
    lua_setfield(L, -2, l_ImGuiDockNodeFlagsPrivate[i].name);
}
lua_setfield(L, -2, "ImGuiDockNodeFlagsPrivate");
lua_newtable(L);
for (int i = 0; l_ImGuiBackendFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiBackendFlags[i].value);
    lua_setfield(L, -2, l_ImGuiBackendFlags[i].name);
}
lua_setfield(L, -2, "ImGuiBackendFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiTabItemFlags[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiTabItemFlags[i].value);
    lua_setfield(L, -2, l_ImGuiTabItemFlags[i].name);
}
lua_setfield(L, -2, "ImGuiTabItemFlags");
lua_newtable(L);
for (int i = 0; l_ImGuiWindowDockStyleCol[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiWindowDockStyleCol[i].value);
    lua_setfield(L, -2, l_ImGuiWindowDockStyleCol[i].name);
}
lua_setfield(L, -2, "ImGuiWindowDockStyleCol");
lua_newtable(L);
for (int i = 0; l_ImGuiTabItemFlagsPrivate[i].name != NULL; i++) {
    lua_pushinteger(L, l_ImGuiTabItemFlagsPrivate[i].value);
    lua_setfield(L, -2, l_ImGuiTabItemFlagsPrivate[i].name);
}
lua_setfield(L, -2, "ImGuiTabItemFlagsPrivate");
    return 1;
}
