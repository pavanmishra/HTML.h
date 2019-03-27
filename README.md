# HTML.h
A simple html generator for C++17

## Create a new tag.

    auto tag = div_({}, {});    
    assert("<div ></div>", renderstring(tag));

## Tags having content.

    auto markup = div_({}, {text("Content")});
    assert(renderstring(markup), "<div>Content</div>");
    auto content = text("Content");
    assert(renderstring(content), "Content");

## Tags having attributes.

     auto markup = div_({lang("tr"), id("content"), class_("bar"), attribute("data-value")("foo")}, {});
     assert(renderstring(markup), "<div lang=\"tr\" id=\"content\" class=\"bar\" data-value=\"foo\"></div>");
     
## Tags with attributes and content.

    auto markup = div_({lang("tr")}, {text("Content")});
    assert(renderstring(markup), "<div lang=\"tr\">Content</div>");

## Nested tags.

    auto markup1 = div_({}, { nav({}, {}), text("Hello"), hr({}, {})});
    assert(renderstring(markup1), "<div><nav></nav>Hello<hr></hr></div>");

    auto markup2 = div_({}, {div_({}, {p({}, {text("a nested paragraph")})})});
    assert(renderstring(markup2), "<div><div><p>a nested paragraph</p></div></div>");

    auto markup3 = html({},
			{ head({}, { title({}, {text("Awesome Website")}),
				script({src("/script.js")}, {})}),
			  body({},
			       { header({},
					{ img({src("/logo.png")}, {}) }),
				   div_({}, {text("Content Here")}),
				   footer({},
					  {hr({}, {}),
					      text("Copyright 2019")})
				   })
			    });
    assert(renderstring(markup3), "<html><head><title>Awesome Website</title><script src=\"/script.js\"></script></head><body><header><img src=\"/logo.png\"></img></header><div>Content Here</div><footer><hr></hr>Copyright 2019</footer></body></html>");


## Composing tags for templating. Showing off Lambda Chops ;).
You can now start having composable abstractions as below.
You can have your own list item which takes content, without need of extra attributes and list syntax for content.
    
    auto li_ = [](std::string item){return li({}, {text(item)});}; 
    auto litems = [=](std::list<std::string> items){
      std::list<Node> result;
      result.resize(items.size());
      std::transform(items.begin(), items.end(), result.begin(), [=](std::string item){ return li_(item);});
      return result;
    };


Abstracting again just because we can.
      
    auto _ul = [=](std::list<std::string> items){return ul({}, litems(items));}; 
    auto markup = _ul({"Bob", "Mary", "Joe"});
    assert(renderstring(markup), "<ul><li>Bob</li><li>Mary</li><li>Joe</li></ul>");
