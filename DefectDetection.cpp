///////////////////////////////////////////////////////////////////////////////
//  File generated by HDevelop for HALCON/C++ Version 12.0
///////////////////////////////////////////////////////////////////////////////



#ifndef __APPLE__
#  include "HalconCpp.h"
#  include "HDevThread.h"
#  if defined(__linux__) && !defined(NO_EXPORT_APP_MAIN)
#    include <X11/Xlib.h>
#  endif
#else
#  ifndef HC_LARGE_IMAGES
#    include <HALCONCpp/HalconCpp.h>
#    include <HALCONCpp/HDevThread.h>
#  else
#    include <HALCONCppxl/HalconCpp.h>
#    include <HALCONCppxl/HDevThread.h>
#  endif
#  include <stdio.h>
#  include <HALCON/HpThread.h>
#  include <CoreFoundation/CFRunLoop.h>
#endif



using namespace HalconCpp;

// Procedure declarations 
// Chapter: Graphics / Text
// Short Description: This procedure displays 'Click 'Run' to continue' in the lower right corner of the screen. 
void disp_continue_message (HTuple hv_WindowHandle, HTuple hv_Color, HTuple hv_Box);
// Chapter: Graphics / Text
// Short Description: This procedure writes a text message. 
void disp_message (HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem, 
    HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box);
// Local procedures 
// Short Description: open window and set part 
void open_zoom_window (HTuple hv_RowPos, HTuple hv_ColPos, HTuple hv_RowROI1, HTuple hv_ColROI1, 
    HTuple hv_RowROI2, HTuple hv_ColROI2, HTuple hv_ZoomFactor, HTuple *hv_WindowHandleZoom);
// Short Description: close zoom window and reset part 
void close_zoom_window (HTuple hv_WindowHandleZoom, HTuple hv_FormerWidth, HTuple hv_FormerHeight);
void initial (HTuple hv_Path, HTuple hv_flag, HTuple *hv_ModelID, HTuple *hv_Width, 
    HTuple *hv_Height);
void find_roi (HObject ho_Image, HObject *ho_ImagePart, HTuple hv_model, HTuple hv_Height, 
    HTuple hv_Width, HTuple *hv_flag);

// Procedures 
// Chapter: Graphics / Text
// Short Description: This procedure displays 'Click 'Run' to continue' in the lower right corner of the screen. 
void disp_continue_message (HTuple hv_WindowHandle, HTuple hv_Color, HTuple hv_Box)
{

  // Local iconic variables

  // Local control variables
  HTuple  hv_ContinueMessage, hv_Row, hv_Column;
  HTuple  hv_Width, hv_Height, hv_Ascent, hv_Descent, hv_TextWidth;
  HTuple  hv_TextHeight;

  //This procedure displays 'Press Run (F5) to continue' in the
  //lower right corner of the screen.
  //It uses the procedure disp_message.
  //
  //Input parameters:
  //WindowHandle: The window, where the text shall be displayed
  //Color: defines the text color.
  //   If set to '' or 'auto', the currently set color is used.
  //Box: If set to 'true', the text is displayed in a box.
  //
  hv_ContinueMessage = "Press Run (F5) to continue";
  GetWindowExtents(hv_WindowHandle, &hv_Row, &hv_Column, &hv_Width, &hv_Height);
  GetStringExtents(hv_WindowHandle, (" "+hv_ContinueMessage)+" ", &hv_Ascent, &hv_Descent, 
      &hv_TextWidth, &hv_TextHeight);
  disp_message(hv_WindowHandle, hv_ContinueMessage, "window", (hv_Height-hv_TextHeight)-12, 
      (hv_Width-hv_TextWidth)-12, hv_Color, hv_Box);
  return;
}

// Chapter: Graphics / Text
// Short Description: This procedure writes a text message. 
void disp_message (HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem, 
    HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box)
{

  // Local iconic variables

  // Local control variables
  HTuple  hv_Red, hv_Green, hv_Blue, hv_Row1Part;
  HTuple  hv_Column1Part, hv_Row2Part, hv_Column2Part, hv_RowWin;
  HTuple  hv_ColumnWin, hv_WidthWin, hv_HeightWin, hv_MaxAscent;
  HTuple  hv_MaxDescent, hv_MaxWidth, hv_MaxHeight, hv_R1;
  HTuple  hv_C1, hv_FactorRow, hv_FactorColumn, hv_UseShadow;
  HTuple  hv_ShadowColor, hv_Exception, hv_Width, hv_Index;
  HTuple  hv_Ascent, hv_Descent, hv_W, hv_H, hv_FrameHeight;
  HTuple  hv_FrameWidth, hv_R2, hv_C2, hv_DrawMode, hv_CurrentColor;

  //This procedure displays text in a graphics window.
  //
  //Input parameters:
  //WindowHandle: The WindowHandle of the graphics window, where
  //   the message should be displayed
  //String: A tuple of strings containing the text message to be displayed
  //CoordSystem: If set to 'window', the text position is given
  //   with respect to the window coordinate system.
  //   If set to 'image', image coordinates are used.
  //   (This may be useful in zoomed images.)
  //Row: The row coordinate of the desired text position
  //   If set to -1, a default value of 12 is used.
  //Column: The column coordinate of the desired text position
  //   If set to -1, a default value of 12 is used.
  //Color: defines the color of the text as string.
  //   If set to [], '' or 'auto' the currently set color is used.
  //   If a tuple of strings is passed, the colors are used cyclically
  //   for each new textline.
  //Box: If Box[0] is set to 'true', the text is written within an orange box.
  //     If set to' false', no box is displayed.
  //     If set to a color string (e.g. 'white', '#FF00CC', etc.),
  //       the text is written in a box of that color.
  //     An optional second value for Box (Box[1]) controls if a shadow is displayed:
  //       'true' -> display a shadow in a default color
  //       'false' -> display no shadow (same as if no second value is given)
  //       otherwise -> use given string as color string for the shadow color
  //
  //Prepare window
  GetRgb(hv_WindowHandle, &hv_Red, &hv_Green, &hv_Blue);
  GetPart(hv_WindowHandle, &hv_Row1Part, &hv_Column1Part, &hv_Row2Part, &hv_Column2Part);
  GetWindowExtents(hv_WindowHandle, &hv_RowWin, &hv_ColumnWin, &hv_WidthWin, &hv_HeightWin);
  SetPart(hv_WindowHandle, 0, 0, hv_HeightWin-1, hv_WidthWin-1);
  //
  //default settings
  if (0 != (hv_Row==-1))
  {
    hv_Row = 12;
  }
  if (0 != (hv_Column==-1))
  {
    hv_Column = 12;
  }
  if (0 != (hv_Color==HTuple()))
  {
    hv_Color = "";
  }
  //
  hv_String = ((""+hv_String)+"").TupleSplit("\n");
  //
  //Estimate extentions of text depending on font size.
  GetFontExtents(hv_WindowHandle, &hv_MaxAscent, &hv_MaxDescent, &hv_MaxWidth, &hv_MaxHeight);
  if (0 != (hv_CoordSystem==HTuple("window")))
  {
    hv_R1 = hv_Row;
    hv_C1 = hv_Column;
  }
  else
  {
    //Transform image to window coordinates
    hv_FactorRow = (1.*hv_HeightWin)/((hv_Row2Part-hv_Row1Part)+1);
    hv_FactorColumn = (1.*hv_WidthWin)/((hv_Column2Part-hv_Column1Part)+1);
    hv_R1 = ((hv_Row-hv_Row1Part)+0.5)*hv_FactorRow;
    hv_C1 = ((hv_Column-hv_Column1Part)+0.5)*hv_FactorColumn;
  }
  //
  //Display text box depending on text size
  hv_UseShadow = 1;
  hv_ShadowColor = "gray";
  if (0 != (HTuple(hv_Box[0])==HTuple("true")))
  {
    hv_Box[0] = "#fce9d4";
    hv_ShadowColor = "#f28d26";
  }
  if (0 != ((hv_Box.TupleLength())>1))
  {
    if (0 != (HTuple(hv_Box[1])==HTuple("true")))
    {
      //Use default ShadowColor set above
    }
    else if (0 != (HTuple(hv_Box[1])==HTuple("false")))
    {
      hv_UseShadow = 0;
    }
    else
    {
      hv_ShadowColor = ((const HTuple&)hv_Box)[1];
      //Valid color?
      try
      {
        SetColor(hv_WindowHandle, HTuple(hv_Box[1]));
      }
      // catch (Exception) 
      catch (HalconCpp::HException &HDevExpDefaultException)
      {
        HDevExpDefaultException.ToHTuple(&hv_Exception);
        hv_Exception = "Wrong value of control parameter Box[1] (must be a 'true', 'false', or a valid color string)";
        throw HalconCpp::HException(hv_Exception);
      }
    }
  }
  if (0 != (HTuple(hv_Box[0])!=HTuple("false")))
  {
    //Valid color?
    try
    {
      SetColor(hv_WindowHandle, HTuple(hv_Box[0]));
    }
    // catch (Exception) 
    catch (HalconCpp::HException &HDevExpDefaultException)
    {
      HDevExpDefaultException.ToHTuple(&hv_Exception);
      hv_Exception = "Wrong value of control parameter Box[0] (must be a 'true', 'false', or a valid color string)";
      throw HalconCpp::HException(hv_Exception);
    }
    //Calculate box extents
    hv_String = (" "+hv_String)+" ";
    hv_Width = HTuple();
    {
    HTuple end_val93 = (hv_String.TupleLength())-1;
    HTuple step_val93 = 1;
    for (hv_Index=0; hv_Index.Continue(end_val93, step_val93); hv_Index += step_val93)
    {
      GetStringExtents(hv_WindowHandle, HTuple(hv_String[hv_Index]), &hv_Ascent, 
          &hv_Descent, &hv_W, &hv_H);
      hv_Width = hv_Width.TupleConcat(hv_W);
    }
    }
    hv_FrameHeight = hv_MaxHeight*(hv_String.TupleLength());
    hv_FrameWidth = (HTuple(0).TupleConcat(hv_Width)).TupleMax();
    hv_R2 = hv_R1+hv_FrameHeight;
    hv_C2 = hv_C1+hv_FrameWidth;
    //Display rectangles
    GetDraw(hv_WindowHandle, &hv_DrawMode);
    SetDraw(hv_WindowHandle, "fill");
    //Set shadow color
    SetColor(hv_WindowHandle, hv_ShadowColor);
    if (0 != hv_UseShadow)
    {
      DispRectangle1(hv_WindowHandle, hv_R1+1, hv_C1+1, hv_R2+1, hv_C2+1);
    }
    //Set box color
    SetColor(hv_WindowHandle, HTuple(hv_Box[0]));
    DispRectangle1(hv_WindowHandle, hv_R1, hv_C1, hv_R2, hv_C2);
    SetDraw(hv_WindowHandle, hv_DrawMode);
  }
  //Write text.
  {
  HTuple end_val115 = (hv_String.TupleLength())-1;
  HTuple step_val115 = 1;
  for (hv_Index=0; hv_Index.Continue(end_val115, step_val115); hv_Index += step_val115)
  {
    hv_CurrentColor = ((const HTuple&)hv_Color)[hv_Index%(hv_Color.TupleLength())];
    if (0 != (HTuple(hv_CurrentColor!=HTuple("")).TupleAnd(hv_CurrentColor!=HTuple("auto"))))
    {
      SetColor(hv_WindowHandle, hv_CurrentColor);
    }
    else
    {
      SetRgb(hv_WindowHandle, hv_Red, hv_Green, hv_Blue);
    }
    hv_Row = hv_R1+(hv_MaxHeight*hv_Index);
    SetTposition(hv_WindowHandle, hv_Row, hv_C1);
    WriteString(hv_WindowHandle, HTuple(hv_String[hv_Index]));
  }
  }
  //Reset changed window settings
  SetRgb(hv_WindowHandle, hv_Red, hv_Green, hv_Blue);
  SetPart(hv_WindowHandle, hv_Row1Part, hv_Column1Part, hv_Row2Part, hv_Column2Part);
  return;
}

// Local procedures 
// Short Description: open window and set part 
void open_zoom_window (HTuple hv_RowPos, HTuple hv_ColPos, HTuple hv_RowROI1, HTuple hv_ColROI1, 
    HTuple hv_RowROI2, HTuple hv_ColROI2, HTuple hv_ZoomFactor, HTuple *hv_WindowHandleZoom)
{

  SetWindowAttr("background_color","black");
  OpenWindow(hv_RowPos,hv_ColPos,(hv_ColROI2-hv_ColROI1)*hv_ZoomFactor,(hv_RowROI2-hv_RowROI1)*hv_ZoomFactor,0,"","",&(*hv_WindowHandleZoom));
  HDevWindowStack::Push((*hv_WindowHandleZoom));
  if (HDevWindowStack::IsOpen())
    SetPart(HDevWindowStack::GetActive(),hv_RowROI1.TupleRound(), hv_ColROI1.TupleRound(), 
        hv_RowROI2.TupleRound(), hv_ColROI2.TupleRound());
  return;
}

// Short Description: close zoom window and reset part 
void close_zoom_window (HTuple hv_WindowHandleZoom, HTuple hv_FormerWidth, HTuple hv_FormerHeight)
{

  HDevWindowStack::SetActive(hv_WindowHandleZoom);
  if (HDevWindowStack::IsOpen())
    CloseWindow(HDevWindowStack::Pop());
  if (HDevWindowStack::IsOpen())
    SetPart(HDevWindowStack::GetActive(),0, 0, hv_FormerHeight-1, hv_FormerWidth-1);
  return;
}

void initial (HTuple hv_Path, HTuple hv_flag, HTuple *hv_ModelID, HTuple *hv_Width, 
    HTuple *hv_Height)
{

  // Local iconic variables
  HObject  ho_ImageModel;

  ReadImage(&ho_ImageModel, hv_Path);
  GetImageSize(ho_ImageModel, &(*hv_Width), &(*hv_Height));
  if (0 != (hv_flag==HTuple("true")))
  {
    //创建模板
    CreateShapeModel(ho_ImageModel, "auto", 0, 6.29, "auto", "auto", "use_polarity", 
        "auto", "auto", &(*hv_ModelID));
    //保存模板
    WriteShapeModel((*hv_ModelID), "E:/modle1.shm");
  }
  else
  {
    //读入模板
    ReadShapeModel("E:/modle1.shm", &(*hv_ModelID));
  }
}

void find_roi (HObject ho_Image, HObject *ho_ImagePart, HTuple hv_model, HTuple hv_Height, 
    HTuple hv_Width, HTuple *hv_flag)
{

  // Local iconic variables
  HObject  ho_img_tmp;

  // Local control variables
  HTuple  hv_Row_origin, hv_Column_origin, hv_Angle_origin;
  HTuple  hv_Score_origin, hv_Row_tmp, hv_Column_tmp, hv_Angle_tmp;
  HTuple  hv_Score_tmp;

  //匹配
  (*hv_flag) = 0;
  FindShapeModel(ho_Image, hv_model, 0, 6.29, 0.5, 1, 0.5, "least_squares", 0, 0, 
      &hv_Row_origin, &hv_Column_origin, &hv_Angle_origin, &hv_Score_origin);
  if (0 != ((hv_Row_origin.TupleLength())==1))
  {
    (*hv_flag) = 2;
    //旋转图片
    RotateImage(ho_Image, &ho_img_tmp, hv_Angle_origin*-57.3248, "constant");
    FindShapeModel(ho_img_tmp, hv_model, 0, 6.29, 0.5, 1, 0.5, "least_squares", 0, 
        0, &hv_Row_tmp, &hv_Column_tmp, &hv_Angle_tmp, &hv_Score_tmp);
    if (0 != ((hv_Row_tmp.TupleLength())==1))
    {
      (*hv_flag) = 1;
      CropPart(ho_img_tmp, &(*ho_ImagePart), hv_Row_tmp-(hv_Height/2), hv_Column_tmp-(hv_Width/2), 
          hv_Width, hv_Height);
    }
  }
}

#ifndef NO_EXPORT_MAIN
// Main procedure 
void action()
{

  // Local iconic variables
  HObject  ho_img, ho_GrayImage, ho_ImageReduced;
  HObject  ho_Region, ho_ConnectedRegions, ho_SelectedRegions;
  HObject  ho_DarkPixels;

  // Local control variables
  HTuple  hv_WindowID, hv_index, hv_img_Width, hv_img_Height;
  HTuple  hv_UsedThreshold;

  //设置窗口大小
  // dev_update_window(...); only in hdevelop
  if (HDevWindowStack::IsOpen())
    CloseWindow(HDevWindowStack::Pop());
  SetWindowAttr("background_color","black");
  OpenWindow(0,0,512,512,0,"","",&hv_WindowID);
  HDevWindowStack::Push(hv_WindowID);

  //遍历图片
  for (hv_index=0; hv_index<=7; hv_index+=1)
  {
    ReadImage(&ho_img, ("E:/python/graphics/origin/origin"+(hv_index.TupleString("1")))+".jpg");
    GetImageSize(ho_img, &hv_img_Width, &hv_img_Height);
    //转灰度图
    Rgb1ToGray(ho_img, &ho_GrayImage);
    //高斯滤波
    GaussFilter(ho_GrayImage, &ho_ImageReduced, 3);
    //二值化
    BinaryThreshold(ho_ImageReduced, &ho_Region, "max_separability", "dark", &hv_UsedThreshold);
    //求连通域
    Connection(ho_Region, &ho_ConnectedRegions);
    //筛选连通域
    SelectShape(ho_ConnectedRegions, &ho_ConnectedRegions, "area", "and", (hv_img_Height*hv_img_Width)/10, 
        ((hv_img_Height*hv_img_Width)*3)/4);
    SelectShape(ho_ConnectedRegions, &ho_ConnectedRegions, "row", "and", hv_img_Height/4, 
        (hv_img_Height*3)/4);
    SelectShape(ho_ConnectedRegions, &ho_ConnectedRegions, "column", "and", hv_img_Width/4, 
        (hv_img_Width*3)/4);
    SelectShape(ho_ConnectedRegions, &ho_ConnectedRegions, "height", "and", hv_img_Height/4, 
        (hv_img_Height*3)/4);
    SelectShape(ho_ConnectedRegions, &ho_ConnectedRegions, "width", "and", hv_img_Width/4, 
        (hv_img_Width*3)/4);
    //腐蚀
    ErosionCircle(ho_ConnectedRegions, &ho_SelectedRegions, 11);
    //抠图
    ReduceDomain(ho_GrayImage, ho_SelectedRegions, &ho_ImageReduced);
    if (HDevWindowStack::IsOpen())
      DispObj(ho_ImageReduced, HDevWindowStack::GetActive());
    DynThreshold(ho_img, ho_ImageReduced, &ho_DarkPixels, 1, "dark");

    disp_continue_message(hv_WindowID, "black", "true");
    // stop(); only in hdevelop
    if (HDevWindowStack::IsOpen())
      ClearWindow(HDevWindowStack::GetActive());
  }


}


#ifndef NO_EXPORT_APP_MAIN

#ifdef __APPLE__
// On OS X systems, we must have a CFRunLoop running on the main thread in
// order for the HALCON graphics operators to work correctly, and run the
// action function in a separate thread. A CFRunLoopTimer is used to make sure
// the action function is not called before the CFRunLoop is running.
HTuple      gStartMutex;
H_pthread_t gActionThread;

static void timer_callback(CFRunLoopTimerRef timer, void *info)
{
  UnlockMutex(gStartMutex);
}

static Herror apple_action(void **parameters)
{
  LockMutex(gStartMutex);
  action();
  CFRunLoopStop(CFRunLoopGetMain());
  return H_MSG_OK;
}

static int apple_main(int argc, char *argv[])
{
  Herror                error;
  CFRunLoopTimerRef     Timer;
  CFRunLoopTimerContext TimerContext = { 0, 0, 0, 0, 0 };

  CreateMutex("type","sleep",&gStartMutex);
  LockMutex(gStartMutex);

  error = HpThreadHandleAlloc(&gActionThread);
  if (H_MSG_OK != error)
  {
    fprintf(stderr,"HpThreadHandleAlloc failed: %d\n", error);
    exit(1);
  }

  error = HpThreadCreate(gActionThread,0,apple_action);
  if (H_MSG_OK != error)
  {
    fprintf(stderr,"HpThreadCreate failed: %d\n", error);
    exit(1);
  }

  Timer = CFRunLoopTimerCreate(kCFAllocatorDefault,
                               CFAbsoluteTimeGetCurrent(),0,0,0,
                               timer_callback,&TimerContext);
  if (!Timer)
  {
    fprintf(stderr,"CFRunLoopTimerCreate failed\n");
    exit(1);
  }
  CFRunLoopAddTimer(CFRunLoopGetCurrent(),Timer,kCFRunLoopCommonModes);
  CFRunLoopRun();
  CFRunLoopRemoveTimer(CFRunLoopGetCurrent(),Timer,kCFRunLoopCommonModes);
  CFRelease(Timer);

  error = HpThreadHandleFree(gActionThread);
  if (H_MSG_OK != error)
  {
    fprintf(stderr,"HpThreadHandleFree failed: %d\n", error);
    exit(1);
  }

  ClearMutex(gStartMutex);
  return 0;
}
#endif

int main(int argc, char *argv[])
{
  // Default settings used in HDevelop (can be omitted) 
  int ret=0;
  SetSystem("width", 512);
  SetSystem("height", 512);

#if defined(_WIN32)
  SetSystem("use_window_thread", "true");
#elif defined(__linux__)
  XInitThreads();
#endif

#ifndef __APPLE__
  action();
#else
  ret = apple_main(argc,argv);
#endif
  return ret;
}

#endif


#endif


