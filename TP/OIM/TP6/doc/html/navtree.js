var NAVTREE =
[
  [ "M1 Informatique - OIM - mini raytracer", "index.html", [
    [ "Page principale", "index.html", null ],
    [ "Pages associées", "pages.html", [
      [ "DEVOIR : Construction et visualisation des solides de Platons", "a00001.html", null ],
      [ "Liste des choses à faire", "a00057.html", null ]
    ] ],
    [ "Modules", "modules.html", [
      [ "Simple Raytracer", "a00050.html", null ],
      [ "Simple Raytracing API", "a00051.html", [
        [ "Color management API", "a00054.html", null ],
        [ "Image management API", "a00056.html", null ],
        [ "Lighting computation API", "a00055.html", null ],
        [ "Ray management API", "a00053.html", null ],
        [ "Scene definition API", "a00052.html", null ]
      ] ]
    ] ],
    [ "Liste des classes", "annotated.html", [
      [ "BSDF", "a00002.html", null ],
      [ "Camera", "a00003.html", null ],
      [ "Color", "a00004.html", null ],
      [ "Cylinder", "a00005.html", null ],
      [ "Diff_Geom", "a00006.html", null ],
      [ "Geometry", "a00007.html", null ],
      [ "Glass", "a00008.html", null ],
      [ "Image", "a00009.html", null ],
      [ "Isect", "a00010.html", null ],
      [ "Light", "a00011.html", null ],
      [ "Material", "a00012.html", null ],
      [ "Matte", "a00013.html", null ],
      [ "Metal", "a00014.html", null ],
      [ "Plane", "a00015.html", null ],
      [ "Plastic", "a00016.html", null ],
      [ "Primitive", "a00017.html", null ],
      [ "Ray", "a00018.html", null ],
      [ "Scene", "a00019.html", null ],
      [ "Sphere", "a00020.html", null ],
      [ "Vector3D", "a00021.html", null ]
    ] ],
    [ "Index des classes", "classes.html", null ],
    [ "Hiérarchie des classes", "hierarchy.html", [
      [ "BSDF", "a00002.html", null ],
      [ "Camera", "a00003.html", null ],
      [ "Color", "a00004.html", null ],
      [ "Diff_Geom", "a00006.html", null ],
      [ "Geometry", "a00007.html", [
        [ "Cylinder", "a00005.html", null ],
        [ "Plane", "a00015.html", null ],
        [ "Sphere", "a00020.html", null ]
      ] ],
      [ "Image", "a00009.html", null ],
      [ "Isect", "a00010.html", null ],
      [ "Light", "a00011.html", null ],
      [ "Material", "a00012.html", [
        [ "Glass", "a00008.html", null ],
        [ "Matte", "a00013.html", null ],
        [ "Metal", "a00014.html", null ],
        [ "Plastic", "a00016.html", null ]
      ] ],
      [ "Primitive", "a00017.html", null ],
      [ "Ray", "a00018.html", null ],
      [ "Scene", "a00019.html", null ],
      [ "Vector3D", "a00021.html", null ]
    ] ],
    [ "Membres de classe", "functions.html", null ],
    [ "Liste des fichiers", "files.html", [
      [ "bsdf.hpp", "a00022.html", null ],
      [ "camera.hpp", "a00023.html", null ],
      [ "color.hpp", "a00024.html", null ],
      [ "cylinder.hpp", "a00025.html", null ],
      [ "diff_geom.hpp", "a00026.html", null ],
      [ "geometry.hpp", "a00027.html", null ],
      [ "glass.hpp", "a00028.html", null ],
      [ "image.hpp", "a00029.html", null ],
      [ "isect.hpp", "a00030.html", null ],
      [ "light.hpp", "a00031.html", null ],
      [ "main.cpp", "a00032.html", null ],
      [ "material.hpp", "a00033.html", null ],
      [ "matte.hpp", "a00034.html", null ],
      [ "metal.hpp", "a00035.html", null ],
      [ "plane.hpp", "a00036.html", null ],
      [ "plastic.hpp", "a00037.html", null ],
      [ "primitive.hpp", "a00038.html", null ],
      [ "ray.hpp", "a00039.html", null ],
      [ "raytracing.cpp", "a00040.html", null ],
      [ "raytracing.h", "a00041.html", null ],
      [ "scene.hpp", "a00042.html", null ],
      [ "solidesplaton.cpp", "a00043.html", null ],
      [ "solidesplaton.h", "a00044.html", null ],
      [ "sphere.hpp", "a00045.html", null ],
      [ "vector3d.hpp", "a00046.html", null ]
    ] ],
    [ "Membres de fichier", "globals.html", null ]
  ] ]
];

function createIndent(o,domNode,node,level)
{
  if (node.parentNode && node.parentNode.parentNode)
  {
    createIndent(o,domNode,node.parentNode,level+1);
  }
  var imgNode = document.createElement("img");
  if (level==0 && node.childrenData)
  {
    node.plus_img = imgNode;
    node.expandToggle = document.createElement("a");
    node.expandToggle.href = "javascript:void(0)";
    node.expandToggle.onclick = function() 
    {
      if (node.expanded) 
      {
        $(node.getChildrenUL()).slideUp("fast");
        if (node.isLast)
        {
          node.plus_img.src = node.relpath+"ftv2plastnode.png";
        }
        else
        {
          node.plus_img.src = node.relpath+"ftv2pnode.png";
        }
        node.expanded = false;
      } 
      else 
      {
        expandNode(o, node, false);
      }
    }
    node.expandToggle.appendChild(imgNode);
    domNode.appendChild(node.expandToggle);
  }
  else
  {
    domNode.appendChild(imgNode);
  }
  if (level==0)
  {
    if (node.isLast)
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2plastnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2lastnode.png";
        domNode.appendChild(imgNode);
      }
    }
    else
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2pnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2node.png";
        domNode.appendChild(imgNode);
      }
    }
  }
  else
  {
    if (node.isLast)
    {
      imgNode.src = node.relpath+"ftv2blank.png";
    }
    else
    {
      imgNode.src = node.relpath+"ftv2vertline.png";
    }
  }
  imgNode.border = "0";
}

function newNode(o, po, text, link, childrenData, lastNode)
{
  var node = new Object();
  node.children = Array();
  node.childrenData = childrenData;
  node.depth = po.depth + 1;
  node.relpath = po.relpath;
  node.isLast = lastNode;

  node.li = document.createElement("li");
  po.getChildrenUL().appendChild(node.li);
  node.parentNode = po;

  node.itemDiv = document.createElement("div");
  node.itemDiv.className = "item";

  node.labelSpan = document.createElement("span");
  node.labelSpan.className = "label";

  createIndent(o,node.itemDiv,node,0);
  node.itemDiv.appendChild(node.labelSpan);
  node.li.appendChild(node.itemDiv);

  var a = document.createElement("a");
  node.labelSpan.appendChild(a);
  node.label = document.createTextNode(text);
  a.appendChild(node.label);
  if (link) 
  {
    a.href = node.relpath+link;
  } 
  else 
  {
    if (childrenData != null) 
    {
      a.className = "nolink";
      a.href = "javascript:void(0)";
      a.onclick = node.expandToggle.onclick;
      node.expanded = false;
    }
  }

  node.childrenUL = null;
  node.getChildrenUL = function() 
  {
    if (!node.childrenUL) 
    {
      node.childrenUL = document.createElement("ul");
      node.childrenUL.className = "children_ul";
      node.childrenUL.style.display = "none";
      node.li.appendChild(node.childrenUL);
    }
    return node.childrenUL;
  };

  return node;
}

function showRoot()
{
  var headerHeight = $("#top").height();
  var footerHeight = $("#nav-path").height();
  var windowHeight = $(window).height() - headerHeight - footerHeight;
  navtree.scrollTo('#selected',0,{offset:-windowHeight/2});
}

function expandNode(o, node, imm)
{
  if (node.childrenData && !node.expanded) 
  {
    if (!node.childrenVisited) 
    {
      getNode(o, node);
    }
    if (imm)
    {
      $(node.getChildrenUL()).show();
    } 
    else 
    {
      $(node.getChildrenUL()).slideDown("fast",showRoot);
    }
    if (node.isLast)
    {
      node.plus_img.src = node.relpath+"ftv2mlastnode.png";
    }
    else
    {
      node.plus_img.src = node.relpath+"ftv2mnode.png";
    }
    node.expanded = true;
  }
}

function getNode(o, po)
{
  po.childrenVisited = true;
  var l = po.childrenData.length-1;
  for (var i in po.childrenData) 
  {
    var nodeData = po.childrenData[i];
    po.children[i] = newNode(o, po, nodeData[0], nodeData[1], nodeData[2],
        i==l);
  }
}

function findNavTreePage(url, data)
{
  var nodes = data;
  var result = null;
  for (var i in nodes) 
  {
    var d = nodes[i];
    if (d[1] == url) 
    {
      return new Array(i);
    }
    else if (d[2] != null) // array of children
    {
      result = findNavTreePage(url, d[2]);
      if (result != null) 
      {
        return (new Array(i).concat(result));
      }
    }
  }
  return null;
}

function initNavTree(toroot,relpath)
{
  var o = new Object();
  o.toroot = toroot;
  o.node = new Object();
  o.node.li = document.getElementById("nav-tree-contents");
  o.node.childrenData = NAVTREE;
  o.node.children = new Array();
  o.node.childrenUL = document.createElement("ul");
  o.node.getChildrenUL = function() { return o.node.childrenUL; };
  o.node.li.appendChild(o.node.childrenUL);
  o.node.depth = 0;
  o.node.relpath = relpath;

  getNode(o, o.node);

  o.breadcrumbs = findNavTreePage(toroot, NAVTREE);
  if (o.breadcrumbs == null)
  {
    o.breadcrumbs = findNavTreePage("index.html",NAVTREE);
  }
  if (o.breadcrumbs != null && o.breadcrumbs.length>0)
  {
    var p = o.node;
    for (var i in o.breadcrumbs) 
    {
      var j = o.breadcrumbs[i];
      p = p.children[j];
      expandNode(o,p,true);
    }
    p.itemDiv.className = p.itemDiv.className + " selected";
    p.itemDiv.id = "selected";
    $(window).load(showRoot);
  }
}

