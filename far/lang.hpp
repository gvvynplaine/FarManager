#ifndef __FARLANG_HPP__
#define __FARLANG_HPP__
/*
lang.hpp

�����䨪���� �஢᪨� ��ப

*/

/* Revision: 1.00 25.06.2000 $ */

/*
Modify:
  25.06.2000 SVS
    ! �����⮢�� Master Copy
    ! �뤥����� � ����⢥ ᠬ����⥫쭮�� �����
*/

enum
{
  MShareware=0,
  MRegistered,
  MYes,
  MNo,
  MOk,
  MCancel,
  MRetry,
  MSkip,
  MDelete,
  MSplit,

  MWarning,
  MError,

  MQuit,
  MAskQuit,
  MF1,
  MF2,
  MF3,
  MF4,
  MF5,
  MF6,
  MF7,
  MF8,
  MF9,
  MF10,
  MF11,
  MF12,

  MAltF1,
  MAltF2,
  MAltF3,
  MAltF4,
  MAltF5,
  MAltF6,
  MAltF7,
  MAltF8,
  MAltF9,
  MAltF10,
  MAltF11,
  MAltF12,

  MCtrlF1,
  MCtrlF2,
  MCtrlF3,
  MCtrlF4,
  MCtrlF5,
  MCtrlF6,
  MCtrlF7,
  MCtrlF8,
  MCtrlF9,
  MCtrlF10,
  MCtrlF11,
  MCtrlF12,

  MShiftF1,
  MShiftF2,
  MShiftF3,
  MShiftF4,
  MShiftF5,
  MShiftF6,
  MShiftF7,
  MShiftF8,
  MShiftF9,
  MShiftF10,
  MShiftF11,
  MShiftF12,

  MHistoryTitle,
  MFolderHistoryTitle,
  MViewHistoryTitle,

  MHistoryView,
  MHistoryEdit,
  MHistoryExt,

  MConfigSystemTitle,
  MConfigRO,
  MConfigRecycleBin,
  MConfigSystemCopy,
  MConfigCopySharing,
  MConfigCreateUppercaseFolders,
  MConfigInactivity,
  MConfigInactivityMinutes,
  MConfigSaveHistory,
  MConfigSaveFoldersHistory,
  MConfigSaveViewHistory,
  MConfigRegisteredTypes,
  MConfigAutoSave,

  MConfigPanelTitle,
  MConfigHidden,
  MConfigHighlight,
  MConfigAutoChange,
  MConfigSelectFolders,
  MConfigReverseSort,
  MConfigShowColumns,
  MConfigShowStatus,
  MConfigShowTotal,
  MConfigShowFree,
  MConfigShowScrollbar,
  MConfigShowScreensNumber,
  MConfigShowSortMode,

  MConfigInterfaceTitle,
  MConfigClock,
  MConfigViewerEditorClock,
  MConfigMouse,
  MConfigKeyBar,
  MConfigMenuBar,
  MConfigSaver,
  MConfigSaverMinutes,
  MConfigDialogsEditHistory,
  MConfigUsePromptFormat,
  MConfigAltGr,
  MConfigCopyTotal,

  MViewConfigTitle,
  MViewConfigExternal,
  MViewConfigExternalF3,
  MViewConfigExternalAltF3,
  MViewConfigExternalCommand,
  MViewConfigInternal,
  MViewConfigSavePos,
  MViewAutoDetectTable,
  MViewConfigTabSize,

  MEditConfigTitle,
  MEditConfigExternal,
  MEditConfigEditorF4,
  MEditConfigEditorAltF4,
  MEditConfigEditorCommand,
  MEditConfigInternal,
  MEditConfigTabsToSpaces,
  MEditConfigPersistentBlocks,
  MEditConfigDelRemovesBlocks,
  MEditConfigAutoIndent,
  MEditConfigSavePos,
  MEditAutoDetectTable,
  MEditConfigTabSize,
  MEditCursorBeyondEnd,

  MSaveSetupTitle,
  MSaveSetupAsk1,
  MSaveSetupAsk2,
  MSaveSetup,

  MCopyDlgTitle,
  MMoveDlgTitle,
  MLinkDlgTitle,
  MCopySecurity,
  MCopyDlgCopy,
  MCopyDlgTree,
  MCopyDlgCancel,
  MCopyDlgRename,
  MCopyDlgLink,
  MCopyDlgTotal,
  MCopyScanning,

  MCopyFile,
  MMoveFile,
  MLinkFile,
  MCopyFiles,
  MMoveFiles,
  MLinkFiles,

  MCopyCopyingTitle,
  MCopyMovingTitle,

  MCopyCannotFind,

  MCannotCopyFolderToItself1,
  MCannotCopyFolderToItself2,

  MCopyCannotCreateFolder,
  MCopyRetry,
  MCopySkip,
  MCopyCancel,

  MCannotCopyFileToItself1,
  MCannotCopyFileToItself2,

  MCopyFileExist,
  MCopySource,
  MCopyDest,
  MCopyOverwrite,
  MCopyOverwriteAll,
  MCopySkipOvr,
  MCopySkipAllOvr,
  MCopyAppend,
  MCopyResume,
  MCopyCancelOvr,

  MCopyFileRO,
  MCopyAskDelete,
  MCopyDeleteRO,
  MCopyDeleteAllRO,
  MCopySkipRO,
  MCopySkipAllRO,
  MCopyCancelRO,

  MCannotCopy,
  MCannotMove,
  MCannotLink,
  MCannotCopyTo,

  MCopyReadError,
  MCopyWriteError,

  MCopyProcessed,
  MCopyMoving,
  MCopyCopying,
  MCopyTo,

  MCopyErrorDiskFull,

  MDeleteTitle,
  MAskDeleteFolder,
  MAskDelete,
  MAskDeleteRecycleFolder,
  MAskDeleteRecycle,
  MAskWipeFolder,
  MAskWipe,
  MAskDeleteFiles,

  MDeleteFolderTitle,
  MDeleteFilesTitle,
  MDeleteFolderConfirm,
  MDeleteFileDelete,
  MDeleteFileAll,
  MDeleteFileSkip,
  MDeleteFileSkipAll,
  MDeleteFileCancel,

  MDeletingTitle,

  MDeleting,

  MDeleteRO,
  MAskDeleteRO,

  MCannotDeleteFile,
  MCannotDeleteFolder,
  MDeleteRetry,
  MDeleteSkip,
  MDeleteCancel,

  MCannotGetSecurity,
  MCannotSetSecurity,

  MEditTitle,
  MAskReload,
  MCurrent,
  MReload,
  MEditCannotOpen,
  MEditReading,
  MEditAskSave,
  MEditSave,
  MEditNotSave,
  MEditContinue,

  MEditRO,
  MEditExists,
  MEditOvr,
  MEditSaving,
  MEditStatusLine,
  MEditStatusCol,

  MEditSearchTitle,
  MEditSearchFor,
  MEditSearchCase,
  MEditSearchReverse,
  MEditSearchSearch,
  MEditSearchCancel,

  MEditReplaceTitle,
  MEditReplaceWith,
  MEditReplaceReplace,

  MEditSearchingFor,
  MEditNotFound,

  MEditAskReplace,
  MEditAskReplaceWith,
  MEditReplace,
  MEditReplaceAll,
  MEditSkip,
  MEditCancel,

  MEditGoToLine,

  MFolderShortcutsTitle,
  MFolderShortcutBottom,
  MShortcutNone,
  MEnterShortcut,

  MEditF1,
  MEditF2,
  MEditF6,
  MEditF7,
  MEditF8,
  MEditF8DOS,
  MEditF10,
  MEditF11,
  MEditF12,

  MEditShiftF2,
  MEditShiftF7,
  MEditShiftF8,
  MEditShiftF10,

  MEditAltF8,

  MEditCtrlF7,

  MEditSaveAs,
  MEditSaveOriginal,
  MEditSaveDOS,
  MEditSaveUnix,
  MEditCannotSave,

  MColumnName,
  MColumnSize,
  MColumnPacked,
  MColumnDate,
  MColumnTime,
  MColumnModified,
  MColumnCreated,
  MColumnAccessed,
  MColumnAttr,
  MColumnDescription,
  MColumnOwner,
  MColumnMumLinks,

  MListUp,
  MListFolder,
  MListMb,
  MListKb,
  MListFileSize,
  MListFilesSize,
  MListFreeSize,

  MDirInfoViewTitle,
  MFileToEdit,

  MUnselectTitle,
  MSelectTitle,

  MCompareTitle,
  MCompareFilePanelsRequired1,
  MCompareFilePanelsRequired2,
  MCompareSameFolders1,
  MCompareSameFolders2,

  MSelectAssocTitle,

  MAssocTitle,
  MAssocBottom,
  MAskDelAssoc,

  MFileAssocTitle,
  MFileAssocMasks,
  MFileAssocDescr,
  MFileAssocExec,
  MFileAssocView,
  MFileAssocEdit,

  MViewF1,
  MViewF2,
  MViewF2Unwrap,
  MViewF3,
  MViewF4,
  MViewF4Text,
  MViewF6,
  MViewF7,
  MViewF8,
  MViewF8DOS,
  MViewF10,
  MViewF11,
  MViewF12,
  MViewShiftF7,
  MViewShiftF8,
  MViewAltF8,

  MInViewer,
  MInEditor,
  MFilterTitle,
  MFilterBottom,
  MNoCustomFilters,
  MPanelFileType,
  MCanEditCustomFilterOnly,
  MAskDeleteFilter,
  MCanDeleteCustomFilterOnly,

  MEnterFilterTitle,
  MFilterMasks,

  MFindFileTitle,
  MFindFileMasks,
  MFindFileText,
  MFindFileCase,
  MFindFileAllTables,
  MFindArchives,
  MSearchAllDisks,
  MSearchFromRoot,
  MSearchFromCurrent,
  MSearchInCurrent,
  MSearchInSelected,
  MFindFileFind,
  MFindFileTable,
  MFindSearchingIn,
  MFindNewSearch,
  MFindGoTo,
  MFindView,
  MFindPanel,
  MFindStop,

  MFindDone,
  MFindCancel,

  MFindFound,

  MFindFileFolder,

  MFoldTreeSearch,

  MGetTableTitle,
  MGetTableNormalText,

  MHelpTitle,
  MCannotOpenHelp,
  MHelpTopicNotFound,

  MHighlightTitle,
  MHighlightBottom,
  MHighlightAskDel,

  MHighlightEditTitle,
  MHighlightMasks,
  MHighlightIncludeAttr,
  MHighlightRO,
  MHighlightHidden,
  MHighlightSystem,
  MHighlightArchive,
  MHighlightCompressed,
  MHighlightFolder,
  MHighlightExcludeAttr,
  MHighlightColors,
  MHighlightNormal,
  MHighlightSelected,
  MHighlightCursor,
  MHighlightSelectedCursor,
  MHighlightMarkChar,

  MInfoTitle,
  MInfoCompName,
  MInfoUserName,
  MInfoRemovable,
  MInfoFixed,
  MInfoNetwork,
  MInfoCDROM,
  MInfoRAM,
  MInfoDisk,
  MInfoDiskTotal,
  MInfoDiskFree,
  MInfoDiskLabel,
  MInfoDiskNumber,
  MInfoMemory,
  MInfoMemoryLoad,
  MInfoMemoryTotal,
  MInfoMemoryFree,
  MInfoVirtualTotal,
  MInfoVirtualFree,
  MInfoDizAbsent,

  MErrorInvalidFunction,
  MErrorBadCommand,
  MErrorFileNotFound,
  MErrorPathNotFound,
  MErrorTooManyOpenFiles,
  MErrorAccessDenied,
  MErrorNotEnoughMemory,
  MErrorDiskRO,
  MErrorDeviceNotReady,
  MErrorCannotAccessDisk,
  MErrorSectorNotFound,
  MErrorOutOfPaper,
  MErrorWrite,
  MErrorRead,
  MErrorDeviceGeneral,
  MErrorFileSharing,
  MErrorNetworkPathNotFound,
  MErrorNetworkBusy,
  MErrorNetworkAccessDenied,
  MErrorNetworkWrite,
  MErrorDiskLocked,
  MErrorFileExists,
  MErrorInvalidName,
  MErrorInsufficientDiskSpace,
  MErrorFolderNotEmpty,
  MErrorIncorrectUserName,
  MErrorIncorrectPassword,
  MErrorLoginFailure,
  MErrorConnectionAborted,
  MErrorCancelled,
  MErrorNetAbsent,
  MErrorNetDeviceInUse,
  MErrorNetOpenFiles,
  MErrorAlreadyAssigned,
  MErrorAlreadyRemebered,
  MErrorNotLoggedOn,
  MErrorInvalidPassword,

  MCannotExecute,
  MScanningFolder,

  MMakeFolderTitle,
  MCreateFolder,
  MCannotCreateFolder,

  MMenuBriefView,
  MMenuMediumView,
  MMenuFullView,
  MMenuWideView,
  MMenuDetailedView,
  MMenuDizView,
  MMenuLongDizView,
  MMenuOwnersView,
  MMenuLinksView,
  MMenuAlternativeView,

  MMenuInfoPanel,
  MMenuTreePanel,
  MMenuQuickView,
  MMenuSortModes,
  MMenuLongNames,
  MMenuTogglePanel,
  MMenuReread,
  MMenuChangeDrive,

  MMenuView,
  MMenuEdit,
  MMenuCopy,
  MMenuMove,
  MMenuCreateFolder,
  MMenuDelete,
  MMenuAdd,
  MMenuExtract,
  MMenuArchiveCommands,
  MMenuAttributes,
  MMenuApplyCommand,
  MMenuDescribe,
  MMenuSelectGroup,
  MMenuUnselectGroup,
  MMenuInvertSelection,
  MMenuRestoreSelection,

  MMenuFindFile,
  MMenuHistory,
  MMenuVideoMode,
  MMenuFindFolder,
  MMenuViewHistory,
  MMenuFoldersHistory,
  MMenuSwapPanels,
  MMenuTogglePanels,
  MMenuCompareFolders,
  MMenuUserMenu,
  MMenuFileAssociations,
  MMenuFolderShortcuts,
  MMenuEditSortGroups,
  MMenuFilter,
  MMenuPluginCommands,
  MMenuWindowsList,
  MMenuProcessList,

  MMenuSystemSettings,
  MMenuPanelSettings,
  MMenuInterface,
  MMenuLanguages,
  MMenuPluginsConfig,
  MMenuConfirmation,
  MMenuFilePanelModes,
  MMenuFileDescriptions,
  MMenuFolderInfoFiles,
  MMenuViewer,
  MMenuEditor,
  MMenuColors,
  MMenuFilesHighlighting,
  MMenuSaveSetup,

  MMenuTogglePanelRight,
  MMenuChangeDriveRight,

  MMenuLeftTitle,
  MMenuFilesTitle,
  MMenuCommandsTitle,
  MMenuOptionsTitle,
  MMenuRightTitle,

  MMenuSortTitle,
  MMenuSortByName,
  MMenuSortByExt,
  MMenuSortByModification,
  MMenuSortBySize,
  MMenuUnsorted,
  MMenuSortByCreation,
  MMenuSortByAccess,
  MMenuSortByDiz,
  MMenuSortByOwner,
  MMenuSortByCompressedSize,
  MMenuSortByNumLinks,
  MMenuSortUseGroups,
  MMenuSortSelectedFirst,

  MChangeDriveTitle,
  MChangeDriveRemovable,
  MChangeDriveFixed,
  MChangeDriveNetwork,
  MChangeDriveCDROM,
  MChangeDriveRAM,
  MChangeDriveLabelAbsent,
  MChangeDriveMb,
  MChangeDriveCannotReadDisk,
  MChangeDriveCannotDisconnect,
  MChangeDriveOpenFiles,
  MChangeDriveAskDisconnect,

  MSearchFileTitle,
  MCannotCreateListFile,

  MDragFiles,
  MDragMove,
  MDragCopy,

  MProcessListTitle,
  MKillProcessTitle,
  MAskKillProcess,
  MKillProcessWarning,
  MKillProcessKill,
  MCannotKillProcess,

  MQuickViewTitle,
  MQuickViewFolder,
  MQuickViewContains,
  MQuickViewFolders,
  MQuickViewFiles,
  MQuickViewBytes,
  MQuickViewCompressed,
  MQuickViewCluster,
  MQuickViewRealSize,
  MQuickViewSlack,

  MSetAttrTitle,
  MSetAttrFor,
  MSetAttrRO,
  MSetAttrArchive,
  MSetAttrHidden,
  MSetAttrSystem,
  MSetAttrCompressed,
  MSetAttrSubfolders,
  MSetAttrFileTime,
  MSetAttrModification,
  MSetAttrCreation,
  MSetAttrLastAccess,
  MSetAttrCurrent,
  MSetAttrSet,

  MSetAttrChange,
  MSetAttrSetClear,

  MSetAttrNTFSOnly,
  MSetAttrTimeTitle1,
  MSetAttrTimeTitle2,
  MSetAttrTimeTitle3,

  MSetAttrSetting,
  MSetAttrCannotFor,
  MSetAttrCompressedCannotFor,
  MSetAttrTimeCannotFor,

  MSetColorPanel,
  MSetColorDialog,
  MSetColorWarning,
  MSetColorMenu,
  MSetColorHMenu,
  MSetColorKeyBar,
  MSetColorCommandLine,
  MSetColorClock,
  MSetColorViewer,
  MSetColorEditor,
  MSetColorHelp,
  MSetDefaultColors,
  MSetBW,

  MSetColorPanelNormal,
  MSetColorPanelSelected,
  MSetColorPanelHighlightedInfo,
  MSetColorPanelDragging,
  MSetColorPanelBox,
  MSetColorPanelNormalCursor,
  MSetColorPanelSelectedCursor,
  MSetColorPanelNormalTitle,
  MSetColorPanelSelectedTitle,
  MSetColorPanelColumnTitle,
  MSetColorPanelTotalInfo,
  MSetColorPanelSelectedInfo,
  MSetColorPanelScrollbar,
  MSetColorPanelScreensNumber,

  MSetColorDialogNormal,
  MSetColorDialogHighlighted,
  MSetColorDialogBox,
  MSetColorDialogBoxTitle,
  MSetColorDialogHighlightedBoxTitle,
  MSetColorDialogTextInput,
  MSetColorDialogUnchangedTextInput,
  MSetColorDialogSelectedTextInput,
  MSetColorDialogButtons,
  MSetColorDialogSelectedButtons,
  MSetColorDialogHighlightedButtons,
  MSetColorDialogSelectedHighlightedButtons,
  MSetColorDialogListText,
  MSetColorDialogSelectedListText,

  MSetColorWarningNormal,
  MSetColorWarningHighlighted,
  MSetColorWarningBox,
  MSetColorWarningBoxTitle,
  MSetColorWarningHighlightedBoxTitle,
  MSetColorWarningTextInput,
  MSetColorWarningButtons,
  MSetColorWarningSelectedButtons,
  MSetColorWarningHighlightedButtons,
  MSetColorWarningSelectedHighlightedButtons,

  MSetColorMenuNormal,
  MSetColorMenuSelected,
  MSetColorMenuHighlighted,
  MSetColorMenuSelectedHighlighted,
  MSetColorMenuBox,
  MSetColorMenuTitle,

  MSetColorHMenuNormal,
  MSetColorHMenuSelected,
  MSetColorHMenuHighlighted,
  MSetColorHMenuSelectedHighlighted,

  MSetColorKeyBarNumbers,
  MSetColorKeyBarNames,
  MSetColorKeyBarBackground,

  MSetColorCommandLineNormal,
  MSetColorCommandLineSelected,

  MSetColorClockNormal,

  MSetColorViewerNormal,
  MSetColorViewerSelected,
  MSetColorViewerStatus,
  MSetColorViewerArrows,

  MSetColorEditorNormal,
  MSetColorEditorSelected,
  MSetColorEditorStatus,

  MSetColorHelpNormal,
  MSetColorHelpHighlighted,
  MSetColorHelpReference,
  MSetColorHelpSelectedReference,
  MSetColorHelpBox,
  MSetColorHelpBoxTitle,
  MSetColorHelpScrollbar,

  MSetColorGroupsTitle,
  MSetColorItemsTitle,

  MSetColorTitle,
  MSetColorForeground,
  MSetColorBackground,
  MSetColorSample,
  MSetColorSet,
  MSetColorCancel,

  MSetConfirmTitle,
  MSetConfirmCopy,
  MSetConfirmMove,
  MSetConfirmDrag,
  MSetConfirmDelete,
  MSetConfirmDeleteFolders,
  MSetConfirmExit,

  MFindFolderTitle,
  MTreeTitle,
  MCannotSaveTree,
  MReadingTree,

  MUserMenuTitle,
  MChooseMenuType,
  MChooseMenuMain,
  MChooseMenuLocal,
  MMainMenuTitle,
  MLocalMenuTitle,
  MAskDeleteMenuItem,
  MEditMenuTitle,
  MEditMenuHotKey,
  MEditMenuLabel,
  MEditMenuCommands,

  MAskInsertMenuOrCommand,
  MMenuInsertCommand,
  MMenuInsertMenu,

  MEditSubmenuTitle,
  MEditSubmenuHotKey,
  MEditSubmenuLabel,

  MViewerTitle,
  MViewerCannotOpenFile,
  MViewerStatusCol,

  MViewSearchTitle,
  MViewSearchFor,
  MViewSearchForText,
  MViewSearchForHex,
  MViewSearchCase,
  MViewSearchReverse,
  MViewSearchSearch,
  MViewSearchCancel,

  MViewSearchingFor,
  MViewSearchCannotFind,

  MPrintTitle,
  MPrintTo,
  MPrintFilesTo,
  MPreparingForPrinting,
  MJobs,
  MCannotOpenPrinter,
  MCannotPrint,

  MSortGroupsTitle,
  MSortGroupsBottom,

  MSortGroupsAskDel,
  MSortGroupsEnter,

  MDescribeFiles,
  MEnterDescription,

  MReadingDiz,
  MCannotUpdateDiz,

  MCfgDizTitle,
  MCfgDizListNames,
  MCfgDizSetHidden,
  MCfgDizStartPos,
  MCfgDizNotUpdate,
  MCfgDizUpdateIfDisplayed,
  MCfgDizAlwaysUpdate,

  MReadingFiles,

  MUserBreakTitle,
  MOperationNotCompleted,

  MEditPanelModes,

  MEditPanelModesBrief,
  MEditPanelModesMedium,
  MEditPanelModesFull,
  MEditPanelModesWide,
  MEditPanelModesDetailed,
  MEditPanelModesDiz,
  MEditPanelModesLongDiz,
  MEditPanelModesOwners,
  MEditPanelModesLinks,
  MEditPanelModesAlternative,

  MEditPanelModeTypes,
  MEditPanelModeWidths,
  MEditPanelModeStatusTypes,
  MEditPanelModeStatusWidths,
  MEditPanelModeFullscreen,
  MEditPanelModeAlignExtensions,
  MEditPanelModeFoldersUpperCase,
  MEditPanelModeFilesLowerCase,
  MEditPanelModeUpperToLowerCase,
  MEditPanelModeCaseSensitiveSort,
  MEditPanelReadHelp,
  MSetFolderInfoTitle,
  MSetFolderInfoNames,

  MScreensTitle,
  MScreensPanels,
  MScreensView,
  MScreensEdit,

  MAskApplyCommandTitle,
  MAskApplyCommand,

  MPluginConfigTitle,
  MPluginCommandsMenuTitle,

  MPreparingList,

  MLangTitle,
  MHelpLangTitle,

  MDefineMacroTitle,
  MDefineMacro,

  MMacroSettingsTitle,
  MMacroSettingsDisableOutput,
  MMacroSettingsRunAfterStart,
  MMacroSettingsIgnoreCommandLine,
  MMacroSettingsEmptyCommandLine,
  MMacroSettingsNotEmptyCommandLine,

  MPluginsHelpTitle,

  MCannotSaveFile,
  MTextSavedToTemp,

  MRegTitle,
  MRegUser,
  MRegCode,
  MRegFailed,
  MRegThanks,
  MRegOnly,
  MRegOnlyShort,
  MListEval,

  MMonthJan,
  MMonthFeb,
  MMonthMar,
  MMonthApr,
  MMonthMay,
  MMonthJun,
  MMonthJul,
  MMonthAug,
  MMonthSep,
  MMonthOct,
  MMonthNov,
  MMonthDec,

  MPluginHotKeyTitle,
  MPluginHotKey,
  MPluginHotKeyBottom,

  MRightCtrl,

  MViewerGoTo,
  MGoToPercent,
  MGoToHex,
  MGoToDecimal,

  MReadFolderError,
};
#endif	// __FARLANG_HPP__
