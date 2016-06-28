#include "stdafx.h"
#include "ObjModel.hpp"



bool ObjModel::loadOBJ(string filePath, string objFile){
    this->filePath = filePath;
    this->objFile = objFile;
    
    cout << "Loading OBJ file " << objFile << endl;
    
    vector<unsigned int> vertexIndices, textureIndices, normalIndices;
    
    vector<vec3> temp_vertices;
    vector<vec2> temp_textures;
    vector<vec3> temp_normals;
    
    
    ObjGroup temp_group;
    
    
    string filename = filePath + "/" + objFile;
    
    FILE* file = fopen(filename.c_str(), "r");
    
    if( file == NULL ){
        printf("Impossible to open the OBJ file !!!\n");
        return false;
    }
    
    while(true){
        
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        
        // else : parse lineHeader
        
        
        
        if (strcmp(lineHeader, "mtllib") == 0 ){
            char ch[128];
            fscanf(file, "%s", ch);
            mtlFile = ch;
            
            loadMTL();
        }
        
        else if (strcmp(lineHeader, "g") == 0 ){
            if (!temp_group.name.empty()){
                groups.push_back(temp_group);
            }
            temp_group.clear();
            
            char chname[128];
            fscanf(file, "%s", chname);
            temp_group.name = chname;
        }
        else if (strcmp(lineHeader, "usemtl") == 0 ){
            if (!temp_group.quads.empty() || !temp_group.triangles.empty()){
                groups.push_back(temp_group);
                temp_group.clear();
            }
            
            char chmtl[128];
            fscanf(file, "%s", chmtl);
            temp_group.material = chmtl;
        }
        else if (strcmp(lineHeader, "v") == 0){
            vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0 ){
            vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            //            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            temp_textures.push_back(uv);
            

        }
        else if (strcmp(lineHeader, "vn") == 0 ){
            vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0 ){
            bool isTriangle = true;
            unsigned int vertexIndex[4], textureIndex[4], normalIndex[4];
            
            for (int k = 0; k < 4; k++){
                char c_s[100];
                fscanf(file, "%s", c_s);
                string s(c_s);
                
                if (k == 3){
                    if (s[0] >= '0' && s[0] <= '9'){
                        isTriangle = false;
                    }
                    else{
                        fseek(file, -s.size(), SEEK_CUR);
                        break;
                    }
                }
                
                int fpos = s.find_first_of('/');
                
                if (fpos == string::npos){
                    vertexIndex[k] = atoi(s.c_str());
                    textureIndex[k] = 0;
                    normalIndex[k] = 0;
                    continue;
                }
                
                vertexIndex[k] = atoi(s.substr(0, fpos).c_str());
                
                int lpos = s.find_last_of('/');
                
                if (fpos == lpos){
                    textureIndex[k] = atoi(s.substr(lpos + 1, s.size() - lpos - 1).c_str());
                    normalIndex[k] = 0;
                }
                else if (lpos == fpos + 1){
                    textureIndex[k] = 0;
                    normalIndex[k] = atoi(s.substr(lpos + 1, s.size() - lpos - 1).c_str());
                }
                else{
                    textureIndex[k] = atoi(s.substr(fpos + 1, lpos - fpos - 1).c_str());
                    normalIndex[k] = atoi(s.substr(lpos + 1, s.size() - lpos - 1).c_str());
                }
                
            }
            
            
            if (isTriangle){
                ObjPoint point[3];
                ObjTriangle triangle;
                
                for (int i = 0; i < 3; i++){
                    point[i].vertex.x = temp_vertices[vertexIndex[i] - 1].x;
                    point[i].vertex.y = temp_vertices[vertexIndex[i] - 1].y;
                    point[i].vertex.z = temp_vertices[vertexIndex[i] - 1].z;
                    
                    if (textureIndex[i] > 0){
                        point[i].texCoord.x = temp_textures[textureIndex[i] - 1].x;
                        point[i].texCoord.y = temp_textures[textureIndex[i] - 1].y;
                    }
                    else{
                        point[i].texCoord.x = -100;
                        point[i].texCoord.y = -100;
                    }
                    
                    if (normalIndex[i] > 0){
                        point[i].normal.x = temp_normals[normalIndex[i] - 1].x;
                        point[i].normal.y = temp_normals[normalIndex[i] - 1].y;
                        point[i].normal.z = temp_normals[normalIndex[i] - 1].z;
                    }
                    else{
                        point[i].normal.x = -100;
                        point[i].normal.y = -100;
                        point[i].normal.z = -100;
                        
                    }
                    triangle.points[i] = point[i];
                }
                temp_group.triangles.push_back(triangle);
            }
            else{
                ObjPoint point[4];
                ObjQuad quad;
                
                for (int i = 0; i < 4; i++){
                    point[i].vertex.x = temp_vertices[vertexIndex[i] - 1].x;
                    point[i].vertex.y = temp_vertices[vertexIndex[i] - 1].y;
                    point[i].vertex.z = temp_vertices[vertexIndex[i] - 1].z;
                    
                    if (textureIndex[i] > 0){
                        point[i].texCoord.x = temp_textures[textureIndex[i] - 1].x;
                        point[i].texCoord.y = temp_textures[textureIndex[i] - 1].y;
                    }
                    else{
                        point[i].texCoord.x = -1;
                        point[i].texCoord.y = -1;
                    }
                    
                    if (normalIndex[i] > 0){
                        point[i].normal.x = temp_normals[normalIndex[i] - 1].x;
                        point[i].normal.y = temp_normals[normalIndex[i] - 1].y;
                        point[i].normal.z = temp_normals[normalIndex[i] - 1].z;
                    }
                    else{
                        point[i].normal.x = -1;
                        point[i].normal.y = -1;
                        point[i].normal.z = -1;
                        
                    }
                    quad.points[i] = point[i];
                }
                temp_group.quads.push_back(quad);
            }
            
        }
        else{
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }
    }
    
    if (!temp_group.triangles.empty() || !temp_group.quads.empty()){
        groups.push_back(temp_group);
    }
    
    if (groups.empty()){
        temp_group.name = "default";
        groups.push_back(temp_group);
    }
    
    setArea();
    return true;
}




bool ObjModel::loadMTL(){
    
    
    cout << "Loading MTL file " << mtlFile << endl;
    
    ObjMaterial temp_mtl;
    
    
    string filename = filePath + "/" + mtlFile;
    
    FILE* file = fopen(filename.c_str(), "r");
    
    if( file == NULL ){
        printf("Impossible to open the file !!!\n");
        return false;
    }
    
    while(true){
        
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        
        // else : parse lineHeader
        
        
        
        if (strcmp(lineHeader, "newmtl") == 0 ){
            cout<<"new mtl"<<endl;
            if (!temp_mtl.name.empty()){
                materials[temp_mtl.name] = temp_mtl;
            }
            temp_mtl.clear();
            char ch[128];
            fscanf(file, "%s", ch);
            temp_mtl.name = ch;
        }
        else if (strcmp(lineHeader, "Kd") == 0 ){
            fscanf(file, "%f %f %f\n", &temp_mtl.diffuse[0], &temp_mtl.diffuse[1], &temp_mtl.diffuse[2]);
            temp_mtl.diffuse[3] = 1.0f;
        }
        else if (strcmp(lineHeader, "Ka") == 0){
            fscanf(file, "%f %f %f\n", &temp_mtl.ambient[0], &temp_mtl.ambient[1], &temp_mtl.ambient[2]);
            temp_mtl.ambient[3] = 1.0f;
        }
        else if (strcmp(lineHeader, "Ks") == 0 ){
            fscanf(file, "%f %f %f\n", &temp_mtl.specular[0], &temp_mtl.specular[1], &temp_mtl.specular[2]);
            temp_mtl.specular[3] = 1.0f;
        }
        else if (strcmp(lineHeader, "Ke") == 0 ){
            fscanf(file, "%f %f %f\n", &temp_mtl.emmissive[0], &temp_mtl.emmissive[1], &temp_mtl.emmissive[2]);
            temp_mtl.emmissive[3] = 1.0f;
        }
        else if (strcmp(lineHeader, "Ns") == 0 ){
            fscanf(file, "%f\n", &temp_mtl.shininess);
        }
        else if (strcmp(lineHeader, "map_Kd") == 0 ){
            char ch[128];
            fscanf(file, "%s", ch);
            GLuint texture;
            glGenTextures(1, &texture);
            temp_mtl.texture = texture;
            cout << ch << endl;
            string texPath = filePath + "/" + ch;
            strcpy(ch, texPath.c_str());
            
        }
        else{
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }
    }
    
    if (!temp_mtl.name.empty()){
        materials[temp_mtl.name] = temp_mtl;
    }
    
    return true;
}





void ObjModel::render(){
    for (int i = 0; i < groups.size(); i++){
        ObjGroup group = groups[i];
        if (!group.material.empty()){
            ObjMaterial material = materials[group.material];
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.diffuse);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess);
            
            if (material.texture < 1000){
                glEnable(GL_COLOR_MATERIAL);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, material.texture);  //选择纹理texture[0]
            }
        }

        
        
        glPushMatrix();

        glBegin(GL_TRIANGLES);
        for (int j = 0; j < group.triangles.size(); j++){
            ObjTriangle triangle = group.triangles[j];
            for (int k = 0; k < 3; k++){
                ObjPoint point = triangle.points[k];
                
                
                if (point.normal.x != -100)
                    glNormal3f(point.normal.x, point.normal.y, point.normal.z);
                if (point.texCoord.x != -100)
                    glTexCoord2f(point.texCoord.x, 1 - point.texCoord.y);
                glVertex3f(point.vertex.x, point.vertex.y, point.vertex.z);            }
        }
        glEnd();
        
        glBegin(GL_QUADS);
        for (int j = 0; j < group.quads.size(); j++){
            ObjQuad quad = group.quads[j];
            for (int k = 0; k < 4; k++){
                ObjPoint point = quad.points[k];
                
                if (point.normal.x != -100)
                    glNormal3f(point.normal.x, point.normal.y, point.normal.z);
                if (point.texCoord.x != -100){
                    glTexCoord2f(point.texCoord.x, 1 - point.texCoord.y);
                }
                glVertex3f(point.vertex.x, point.vertex.y, point.vertex.z);
            }
        }
        glEnd();
        
        glPopMatrix();
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_TEXTURE_2D);
    }
}



void ObjModel::unitize(GLfloat ratio){
    GLfloat maxx, minx, maxy, miny, maxz, minz;
    GLfloat cx, cy, cz, w, h, d;
    GLfloat scale;
    

    maxx = maxy = maxz = -10000;
    minx = miny = minz = 10000;
    
    for (int i = 0; i < groups.size(); i++){
        ObjGroup group = groups[i];
        for (int j = 0; j < group.triangles.size(); j++){
            ObjTriangle triangle = group.triangles[j];
            for (int k = 0; k < 3; k++){
                ObjPoint point = triangle.points[k];
                if (point.vertex.x < minx)
                    minx = point.vertex.x;
                if (point.vertex.x > maxx)
                    maxx = point.vertex.x;
                
                if (point.vertex.y < miny)
                    miny = point.vertex.y;
                if (point.vertex.y > maxy)
                    maxy = point.vertex.y;
                
                if (point.vertex.z < minz)
                    minz = point.vertex.z;
                if (point.vertex.z > maxz)
                    maxz = point.vertex.z;
            }
        }
        for (int j = 0; j < group.quads.size(); j++){
            ObjQuad quad = group.quads[j];
            for (int k = 0; k < 4; k++){
                ObjPoint point = quad.points[k];
                if (point.vertex.x < minx)
                    minx = point.vertex.x;
                if (point.vertex.x > maxx)
                    maxx = point.vertex.x;
                
                if (point.vertex.y < miny)
                    miny = point.vertex.y;
                if (point.vertex.y > maxy)
                    maxy = point.vertex.y;
                
                if (point.vertex.z < minz)
                    minz = point.vertex.z;
                if (point.vertex.z > maxz)
                    maxz = point.vertex.z;
            }
        }
    }
    

    w = maxx - minx;
    h = maxy - miny;
    d = maxz - minz;
    

    /* calculate center of the model */
    cx = (maxx + minx) / 2.0;
    cy = (maxy + miny) / 2.0;
    cz = (maxz + minz) / 2.0;
    
    
    scale = ratio / max(max(w, h), d);


    for (int i = 0; i < groups.size(); i++){
        ObjGroup group = groups[i];
        for (int j = 0; j < group.triangles.size(); j++){
            ObjTriangle triangle = group.triangles[j];
            for (int k = 0; k < 3; k++){
                ObjPoint point = triangle.points[k];
                point.vertex.x -= cx;
                point.vertex.y -= cy;
                point.vertex.z -= cz;
                
                point.vertex.x *= scale;
                point.vertex.y *= scale;
                point.vertex.z *= scale;
                
                groups[i].triangles[j].points[k].vertex.x = point.vertex.x;
                groups[i].triangles[j].points[k].vertex.y = point.vertex.y;
                groups[i].triangles[j].points[k].vertex.z = point.vertex.z;
            }
        }
        for (int j = 0; j < group.quads.size(); j++){
            ObjQuad quad = group.quads[j];
            for (int k = 0; k < 4; k++){
                ObjPoint point = quad.points[k];
                point.vertex.x -= cx;
                point.vertex.y -= cy;
                point.vertex.z -= cz;
                
                point.vertex.x *= scale;
                point.vertex.y *= scale;
                point.vertex.z *= scale;
                
                groups[i].quads[j].points[k].vertex.x = point.vertex.x;
                groups[i].quads[j].points[k].vertex.y = point.vertex.y;
                groups[i].quads[j].points[k].vertex.z = point.vertex.z;            }
        }
    }
    setArea();
}


void ObjModel::getDimensions(GLfloat* dimensions){
    GLfloat maxx, minx, maxy, miny, maxz, minz;
    GLfloat cx, cy, cz, w, h, d;
    GLfloat scale;
    
    
    maxx = maxy = maxz = -10000;
    minx = miny = minz = 10000;
    
    for (int i = 0; i < groups.size(); i++){
        ObjGroup group = groups[i];
        for (int j = 0; j < group.triangles.size(); j++){
            ObjTriangle triangle = group.triangles[j];
            for (int k = 0; k < 3; k++){
                ObjPoint point = triangle.points[k];
                if (point.vertex.x < minx)
                    minx = point.vertex.x;
                if (point.vertex.x > maxx)
                    maxx = point.vertex.x;
                
                if (point.vertex.y < miny)
                    miny = point.vertex.y;
                if (point.vertex.y > maxy)
                    maxy = point.vertex.y;
                
                if (point.vertex.z < minz)
                    minz = point.vertex.z;
                if (point.vertex.z > maxz)
                    maxz = point.vertex.z;
            }
        }
        for (int j = 0; j < group.quads.size(); j++){
            ObjQuad quad = group.quads[j];
            for (int k = 0; k < 4; k++){
                ObjPoint point = quad.points[k];
                if (point.vertex.x < minx)
                    minx = point.vertex.x;
                if (point.vertex.x > maxx)
                    maxx = point.vertex.x;
                
                if (point.vertex.y < miny)
                    miny = point.vertex.y;
                if (point.vertex.y > maxy)
                    maxy = point.vertex.y;
                
                if (point.vertex.z < minz)
                    minz = point.vertex.z;
                if (point.vertex.z > maxz)
                    maxz = point.vertex.z;
            }
        }
    }

    w = maxx - minx;
    h = maxy - miny;
    d = maxz - minz;
    
    dimensions[0] = w;
    dimensions[1] = h;
    dimensions[2] = d;
}

GLfloat ObjModel::getMinY(){
    GLfloat miny = 10000;
    for (int i = 0; i < groups.size(); i++){
        ObjGroup group = groups[i];
        for (int j = 0; j < group.triangles.size(); j++){
            ObjTriangle triangle = group.triangles[j];
            for (int k = 0; k < 3; k++){
                ObjPoint point = triangle.points[k];
                if (point.vertex.y < miny)
                    miny = point.vertex.y;
            }
        }
        for (int j = 0; j < group.quads.size(); j++){
            ObjQuad quad = group.quads[j];
            for (int k = 0; k < 4; k++){
                ObjPoint point = quad.points[k];
                if (point.vertex.y < miny)
                    miny = point.vertex.y;
            }
        }
    }
    return miny;
}

GLfloat ObjModel::getMinX(){
    GLfloat minx = 10000;
    for (int i = 0; i < groups.size(); i++){
        ObjGroup group = groups[i];
        for (int j = 0; j < group.triangles.size(); j++){
            ObjTriangle triangle = group.triangles[j];
            for (int k = 0; k < 3; k++){
                ObjPoint point = triangle.points[k];
                if (point.vertex.x < minx)
                    minx = point.vertex.x;
            }
        }
        for (int j = 0; j < group.quads.size(); j++){
            ObjQuad quad = group.quads[j];
            for (int k = 0; k < 4; k++){
                ObjPoint point = quad.points[k];
                if (point.vertex.x < minx)
                    minx = point.vertex.x;
            }
        }
    }
    return minx;
}

GLfloat ObjModel::getMinZ(){
    GLfloat minz = 10000;
    for (int i = 0; i < groups.size(); i++){
        ObjGroup group = groups[i];
        for (int j = 0; j < group.triangles.size(); j++){
            ObjTriangle triangle = group.triangles[j];
            for (int k = 0; k < 3; k++){
                ObjPoint point = triangle.points[k];
                if (point.vertex.z < minz)
                    minz = point.vertex.z;
            }
        }
        for (int j = 0; j < group.quads.size(); j++){
            ObjQuad quad = group.quads[j];
            for (int k = 0; k < 4; k++){
                ObjPoint point = quad.points[k];
                if (point.vertex.z < minz)
                    minz = point.vertex.z;
            }
        }
    }
    return minz;
}


GLuint ObjModel::list()
{
    GLuint list;
    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    render();
    glEndList();
    return list;
}



void ObjModel::setPosition(GLfloat x, GLfloat y, GLfloat z){
    position.x = x;
    position.y = y;
    position.z = z;
    setArea();
}



void ObjModel::draw(){
    if (objList == 10000)
        objList = list();
	glColor3f(0.8f,0.7f,0.6f);
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotated(ori, 0, 1, 0);
    glCallList(objList);
    glPopMatrix();
}

//添加旋转信息
void ObjModel::setArea(){
    area.x = getMinX() + position.x;
    area.y = getMinY() + position.y;
    area.z = getMinZ() + position.z;
    getDimensions(area.dimensions);
}

Area& ObjModel::getArea(){
    setArea();
    return area;
}


void ObjModel::rotate(GLuint ori){
    this->ori = ori;
}

