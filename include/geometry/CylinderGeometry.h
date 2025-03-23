#include <math.h>
#include <geometry/BufferGeometry.h>

#ifndef CYLINDER_GROMETRY
#define CYLINDER_GROMETRY
#define PI acos(-1)


using namespace std;

class CylinderGeometry : public BufferGeometry
{
public:
 //上圆半径 下圆半径 高度 圆面层数 柱面高度层数 是否不画圆面 起始水平视角 水平绘画角度
  CylinderGeometry( float radiusTop = 1, float radiusBottom = 1,float  height = 1, float radialSegments = 32,float  heightSegments = 1, bool openEnded = false, float thetaStart = 0, float thetaLength = PI * 2 )
  {

    radialSegments = glm::floor(radialSegments);
    heightSegments = glm::floor(heightSegments);
    int index = 0;
    float halfHeight = height/2;
    int groupStart = 0;
	int groupCount = 0;

    //vector<vector<int>> grid;
    //glm::vec3 position = glm::vec3(0.0f);
    /**
     * 三分量对应
     * vec3(u, v, w)
     * x y z | 0, 1, 2
     * z y x | 2, 1, 0
     * x z y | 0, 2, 1
     */
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 normal = glm::vec3(0.0f);
    Vertex vertex;
    vector<vector<int>> indexArray;
    float slope = ( radiusBottom - radiusTop ) / height;
    // 计算 顶点坐标 法向量 和 纹理坐标
    for ( int y = 0; y <= heightSegments; y ++ ) {

                vector<int> indexRow;
				float v = y / heightSegments;


				float radius = v * ( radiusBottom - radiusTop ) + radiusTop;

				for ( int x = 0; x <= radialSegments; x ++ ) {

					float u = x / radialSegments;

					float theta = u * thetaLength + thetaStart;

					float sinTheta = sin( theta );
					float cosTheta = cos( theta );

					// 顶点

					position.x = radius * sinTheta;
					position.y = - v * height + halfHeight;
					position.z = radius * cosTheta;
					vertex.Position = position;

					// 法向量
                   glm::vec3 tt = glm::vec3(sinTheta , slope , cosTheta);
				   normal = glm::normalize(tt);
				   vertex.Normal = normal;

					// 纹理

					vertex.TexCoords = glm::vec2(u , 1 - v );


					indexRow.push_back( index ++ );
                    this->vertices.push_back(vertex);

				}


				indexArray.push_back( indexRow );

			}

            //indices
            for ( int x = 0; x < radialSegments; x ++ ) {

				for ( int y = 0; y < heightSegments; y ++ ) {


					int a = indexArray[ y ][ x ];
					int b = indexArray[ y + 1 ][ x ];
					int c = indexArray[ y + 1 ][ x + 1 ];
					int d = indexArray[ y ][ x + 1 ];


					this->indices.push_back(a);
                    this->indices.push_back(b);
                    this->indices.push_back(d);
                    
					this->indices.push_back(b);
                    this->indices.push_back(c);
                    this->indices.push_back(d);

                    groupCount += 6;

				}

			}




    if ( openEnded == false ) {

		if ( radiusTop > 0 ){
			int centerIndexStart = index;


			int groupCount = 0;

			float radius = radiusTop;
			float sign = 1;


			for ( int x = 1; x <= radialSegments; x ++ ) {

				// 顶点
                position.x = 0;
                position.y = halfHeight * sign;
                position.z = 0;
				vertex.Position = position;

				// 法向量
                glm::vec3 tt = glm::vec3(0 , sign , 0);
				normal = glm::normalize(tt);
				vertex.Normal = normal;

				// 纹理

                vertex.TexCoords = glm::vec2(0.5 , 0.5 );

                this->vertices.push_back(vertex);
				index++;

			}

			int centerIndexEnd = index;


			for ( int x = 0; x <= radialSegments; x ++ ) {

				float u = x / radialSegments;
				float theta = u * thetaLength + thetaStart;

				float cosTheta = cos( theta );
				float sinTheta = sin( theta );

				// 顶点

				position.x = radius * sinTheta;
				position.y = halfHeight * sign;
				position.z = radius * cosTheta;
				vertex.Position = position;

				// 法向量
                glm::vec3 tt = glm::vec3(0 , sign , 0);
				normal = glm::normalize(tt);
				vertex.Normal = normal;

				// 纹理

				float tx = ( cosTheta * 0.5 ) + 0.5;
				float ty = ( sinTheta * 0.5 * sign ) + 0.5;
                vertex.TexCoords = glm::vec2(tx , ty);

                this->vertices.push_back(vertex);
				index ++;

			}


			for ( int x = 0; x < radialSegments; x ++ ) {

				float c = centerIndexStart + x;
				float i = centerIndexEnd + x;



                    this->indices.push_back(i);
                    this->indices.push_back(i+1);
                    this->indices.push_back(c);



				groupCount += 3;

			}


			groupStart += groupCount;

		}
		if ( radiusBottom > 0 ){
			int centerIndexStart = index;


			int groupCount = 0;

			float radius = radiusBottom;
			float sign = -1;


			for ( int x = 1; x <= radialSegments; x ++ ) {

				// 顶点
                position.x = 0;
                position.y = halfHeight * sign;
                position.z = 0;
				vertex.Position = position;

				// 法向量
                glm::vec3 tt = glm::vec3(0 , sign , 0);
				normal = glm::normalize(tt);
				vertex.Normal = normal;

				// 纹理

                vertex.TexCoords = glm::vec2(0.5, 0.5 );

                this->vertices.push_back(vertex);
				index++;

			}

			int centerIndexEnd = index;


			for ( int x = 0; x <= radialSegments; x ++ ) {

				float u = x / radialSegments;
				float theta = u * thetaLength + thetaStart;

				float cosTheta = cos( theta );
				float sinTheta = sin( theta );

				// 顶点

				position.x = radius * sinTheta;
				position.y = halfHeight * sign;
				position.z = radius * cosTheta;
				vertex.Position = position;

				// 法向量
                glm::vec3 tt = glm::vec3(0 , sign , 0);
				normal = glm::normalize(tt);
				vertex.Normal = normal;

				// 纹理

				float tx = ( cosTheta * 0.5 ) + 0.5;
				float ty = ( sinTheta * 0.5 * sign ) + 0.5;
                vertex.TexCoords = glm::vec2(tx , ty);

                this->vertices.push_back(vertex);
				index ++;

			}


			for ( int x = 0; x < radialSegments; x ++ ) {

				float c = centerIndexStart + x;
				float i = centerIndexEnd + x;



                    this->indices.push_back(i+1);
                    this->indices.push_back(i);
                    this->indices.push_back(c);



				groupCount += 3;

			}


			groupStart += groupCount;
        };

	};
    

    this->setupBuffers();
  }
};

#endif