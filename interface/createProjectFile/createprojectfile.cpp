#include "createprojectfile.hpp"

createProjectFile::createProjectFile(string theProjectName, string theProjectDir,
                                      string theMethod, string theDatabaseType,string theDatabaseDir)
{


  projectName = theProjectName;
  projectDir = theProjectDir;
  databaseType = theDatabaseType;
  databaseDir = theDatabaseDir;
method = theMethod;
  QString pDir, dDir;
  QDir dir(pDir);

  pDir = pDir.fromStdString(projectDir);
if(!dir.exists(pDir))
      dir.mkpath(pDir);


projectFile.open(projectDir + "/" + projectName+".proj");
  projectInfo = YAML::LoadFile(projectDir + "/" + projectName+".proj");


  projectInfo["project"]["projectName"] = projectName;
  projectInfo["project"]["method"]["name"] = method;
cout << method << endl;
  if(method == "KFDA")
    {
      projectInfo["project"]["method"]["kernelType"]["name"] = NULL;
      projectInfo["project"]["method"]["kernelType"]["variance"] = NULL;
    }
  else if(method == "FLDA")
    {

    }
  projectInfo["project"]["method"]["Dimension after PCA"] = NULL;
  projectInfo["project"]["status"]="untrained";
  setDatabase();


}

void createProjectFile::setDatabase()
{

      projectInfo["project"]["database"]["type"] = databaseType;
      projectInfo["project"]["database"]["directory"] = databaseDir;
      projectInfo["project"]["database"]["trains"] = NULL;

}
void createProjectFile::setRBF(double variance)
{
  projectInfo["project"]["method"]["kernelType"]["variance"] = variance;
}
void createProjectFile::close()
{
  projectFile << projectInfo;
  projectFile.close();

}
