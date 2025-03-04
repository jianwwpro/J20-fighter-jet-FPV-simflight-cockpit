void draw_new_attitude(){

  //覆盖原姿态线
  //spr.fillRect(1,1,x_limit-1,y_limit-1,GREEN);  
  // spr.fillTriangle(xb5,yb5,xb6,yb6,xb7,yb7,BLUE);
  // spr.fillTriangle(xb8,yb8,xb6,yb6,xb7,yb7,BLUE);
  spr.fillRect(1,1,x_limit-1,y_limit-1,0xC460);  //地面土黄色
  spr.fillTriangle(xb5,yb5,xb6,yb6,xb7,yb7,0x5D1C); //天空淡绿色
  spr.fillTriangle(xb8,yb8,xb6,yb6,xb7,yb7,0x5D1C); //天空淡绿色
  
  // 绘制罗盘仪
  const int compass_center_x = x_limit/2;
  const int compass_center_y = 75;  // 罗盘中心Y坐标
  const int compass_radius = 70;    // 罗盘半径
  const int tick_length = 8;        // 刻度线长度
  
  // 绘制罗盘外弧
  const float arc_start = 120;  // 弧形开始角度
  const float arc_end = 240;    // 弧形结束角度
  spr.drawSmoothArc(compass_center_x, compass_center_y, compass_radius, compass_radius-2, arc_start, arc_end, YELLOW, BLACK, false);
  
  /*
  // 固定的指示标（位于正上方）
  const int triangle_size = 6;
  const int triangle_base_y = compass_center_y - compass_radius + 2;
  spr.fillTriangle(
    compass_center_x, triangle_base_y,
    compass_center_x - triangle_size, triangle_base_y + triangle_size,
    compass_center_x + triangle_size, triangle_base_y + triangle_size,
    RED
  );
  */
  
  // 计算罗盘旋转角度
  float compass_rotation = radians(heading-90);
  
  // 绘制旋转的刻度和标签
  for(float base_angle = 0; base_angle < 360; base_angle += 30) {
    // 计算实际旋转后的角度
    float rotated_angle = radians(base_angle) - compass_rotation;
    
    // 计算显示角度（用于判断是否在可见范围内）
    float display_angle = fmod(degrees(PI-rotated_angle) + 360, 360);
    
    // 只在弧度线范围内显示刻度
    if(display_angle >= 30 && display_angle <= 150) {
      // 计算刻度线的起点和终点
      int start_x = compass_center_x + cos(PI-rotated_angle) * compass_radius;
      int start_y = compass_center_y - sin(PI-rotated_angle) * compass_radius;
      int end_x = compass_center_x + cos(PI-rotated_angle) * (compass_radius - tick_length);
      int end_y = compass_center_y - sin(PI-rotated_angle) * (compass_radius - tick_length);
      
      spr.drawLine(start_x, start_y, end_x, end_y, YELLOW);
      
      // 添加方向标签
      spr.setTextColor(YELLOW);
      spr.setTextSize(1);
      
      // 计算标签位置
      int label_x = compass_center_x + cos(PI-rotated_angle) * (compass_radius - 15);
      int label_y = compass_center_y - sin(PI-rotated_angle) * (compass_radius - 15);
      
      // 计算实际航向角度
      int actual_heading = int(fmod(base_angle - degrees(compass_rotation) + 360, 360));
      
      // 根据实际航向角度确定显示的方向标签
      String direction = "";
      if(base_angle == 0 || base_angle == 360) {
        direction = "N";
      } else if(base_angle == 90) {
        direction = "E";
      } else if(base_angle == 180) {
        direction = "S";
      } else if(base_angle == 270) {
        direction = "W";
      } else {
        direction = String(base_angle,0);
      }
      
      // 调整标签位置以避免重叠
      int label_offset = direction.length() > 1 ? 8 : 4;
      spr.drawString(direction, label_x-label_offset, label_y-4);
    }
  }
  
 

  // 原有的姿态仪代码
  spr.loadFont(NotoSansMonoSCB20);  

  // 画出i范围level的新的姿态线, i的范围是0-6，
  spr.drawRect(0,0,x_limit,y_limit,YELLOW);//画出姿态线的框框
  spr.fillTriangle(x_center, y_center,x_center-35,y_center+9,x_center+35,y_center+9, RED);//画出飞机标记
  
  for (int i=1; i < 6; i++) {
    //base_vect*level_angle得到离姿态仪中心最近的姿态线角度
    draw_level_angle = base_vect*level_angle+(i-3)*level_angle; // i-3 在for循环中，得到-2，-1， 0， 1, 2 三根姿态线编号，0号姿态线就是离姿态仪中心最近的姿态线
    if (draw_level_angle < 0){
      color = BLACK;      
    } else{
      color = WHITE;
    }
    
    itoa(draw_level_angle, level_char, 10);        
    //判断长的0度地平线左边一半线段坐标是否在画布范围内
    if ((draw_level_angle == 0) && (xb1>1) && (xb1<x_limit) && (xb2>1) && (xb2<x_limit) && (yb1>1) && (yb1<y_limit) && (yb2>1)  && (yb2<y_limit)){
      spr.drawWideLine(xb1, yb1, xb2, yb2, 4, color); //画一根长的地平线
    } else {
        if((att_points[i][0]>1) && (att_points[i][0]<x_limit) && (att_points[i][1]>1)  && (att_points[i][1]<y_limit) && (att_points[i][2]>1) && (att_points[i][2]<x_limit)  && (att_points[i][3]>1) && (att_points[i][3]<y_limit) ) {
          spr.drawWideLine(att_points[i][0], att_points[i][1], att_points[i][2], att_points[i][3], 2, color);
        }       
      } //else

    //判断长的0度地平线右边一半线段坐标是否在画布范围内
    if ((draw_level_angle == 0) && (xb3>1) && (xb4>1) && (xb3<x_limit) && (xb4<x_limit) && (yb3>1) && (yb4>1) && (yb3<y_limit) && (yb4<y_limit) ){
      spr.drawWideLine(xb3, yb3, xb4, yb4, 4, color); //画一根长的地平线
      } else {
        if((att_points[i][4]>1) && (att_points[i][4]<x_limit) && (att_points[i][5]>1)  && (att_points[i][5]<y_limit) && (att_points[i][6]>1) && (att_points[i][6]<x_limit)  && (att_points[i][7]>1) && (att_points[i][7]<y_limit) )  {          
          spr.drawWideLine(att_points[i][4], att_points[i][5], att_points[i][6], att_points[i][7], 2, color);
          
        }
      }//else  

    // *****************写上pitch度数**********************
    if (draw_level_angle == 0 ){
      spr.setCursor((att_points[i][0]+att_points[i][6])/2 - 5, (att_points[i][1]+att_points[i][7])/2 - 10);
      spr.setTextColor(color);
      spr.println(level_char);    
    }
    if (draw_level_angle > 0 ){
      spr.setCursor((att_points[i][0]+att_points[i][6])/2 - 10, (att_points[i][1]+att_points[i][7])/2 - 10);
      spr.setTextColor(color);
      spr.println(level_char);    
    }
    if (draw_level_angle < 0 ){
      spr.setCursor((att_points[i][0]+att_points[i][6])/2 - 15, (att_points[i][1]+att_points[i][7])/2 - 10);
      spr.setTextColor(color);
      spr.println(level_char);    
    }

  } // for loop
  spr.unloadFont();
  // memcpy(old_att_points, att_points, 7*8*sizeof(att_points[0][0]));
  // old_xb1=xb1 , old_xb2=xb2, old_xb3=xb3, old_xb4=xb4, old_yb1=yb1, old_yb2=yb2, old_yb3=yb3, old_yb4=yb4;
  // old_base_vect = base_vect;
  //记得手动改颜色

/*
   // 显示数字航向角（红色）
  spr.setTextColor(RED);
  spr.loadFont(NotoSansMonoSCB20);
  String heading_str = String(heading);
  int text_width = heading_str.length() * 12;
  spr.setCursor(compass_center_x - text_width/2, compass_center_y - compass_radius + 130);
  spr.print(heading_str);
  spr.unloadFont();
  */
}


