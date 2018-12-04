#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glut.h>
using namespace std;

class MapPoint
{
  public:
    double longitude;
    double latitude;
};
class Polygon
{
  public:
    vector<MapPoint> points; //多边形的顶点序列
};
vector<Polygon *> polys; //多边形集合
vector<Polygon *> ReadMapData(char *filename)
{
    int PointCount;
    vector<Polygon *> polygons;
    ifstream fs(filename);
    while (fs.eof() != true)
    {
        Polygon *poly = new Polygon;
        fs >> PointCount;
        cout << PointCount << endl;
        for (int i = 0; i < PointCount; i++)
        {
            MapPoint p;
            fs >> p.longitude >> p.latitude;
            poly->points.push_back(p);
        }
        polygons.push_back(poly);
    }
    return polygons;
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //用蓝色色绘制各省边界
    glColor3f(0.0, 0.0, 1.0);
    glPolygonMode(GL_BACK, GL_LINE);
    for (int i = 0; i < polys.size(); i++)
    {
        vector<MapPoint> points = polys[i]->points;
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < points.size(); j++)
        {
            glVertex3f(points[j].longitude, points[j].latitude, 0.0);
        }
        glEnd();
    }
    glFlush();
}
void init(void)
{
    //设置背景颜色
    glClearColor(1.0, 1.0, 1.0, 0.0);
    //初始化观察值
    glMatrixMode(GL_PROJECTION);                  //将矩阵模式设为投影
    glLoadIdentity();                             //对矩阵进行单位化    
    //glOrtho(110.0, 118.0, 30.0, 38.0, -1.0, 1.0);
    glOrtho(116.714523, 118.078628, 38.561241, 40.257573, -1.0, 1.0); //构造平行投影矩阵
}
int main(int argc, char **argv)
{
    //数据文件请到http://files.cnblogs.com/opengl/HenanCounty.rar下载放到D盘根目录下并解压
    char *filename = "tianjin.txt";

    polys = ReadMapData(filename);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //单缓存和RGB
    glutInitWindowSize(380, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("地图绘制");
    init();
    glutDisplayFunc(display); //显示回调函数
    glutMainLoop();
    return 0;
}