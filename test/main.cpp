#define CATCH_CONFIG_MAIN 
#include <catch2/catch.hpp>
#include "html.hpp"


TEST_CASE("Rendering with building material.", "[HTML BASE]"){
  REQUIRE(renderstring(text("Hello HTML.h")) == "Hello HTML.h");
  REQUIRE(renderstring(element("hr")({}, {})) == "<hr></hr>");
}

TEST_CASE( "HTML is rendered.", "[HTML]" ) {

  SECTION( "Create a new tag."){
    auto tag = div_({}, {});
    REQUIRE(renderstring(tag) == "<div></div>");
  }

  SECTION("Tags having content."){
    auto markup = div_({}, {text("Content")});
    REQUIRE(renderstring(markup) == "<div>Content</div>");
  }

  SECTION("Tags having attributes."){
    auto markup = div_({lang("tr"), id("content"), class_("bar"), attribute("data-value")("foo")}, {});
    REQUIRE(renderstring(markup) == "<div lang=\"tr\" id=\"content\" class=\"bar\" data-value=\"foo\"></div>");
  }

  SECTION("Tags with attributes and content."){
    auto markup = div_({lang("tr")}, {text("Content")});
    REQUIRE(renderstring(markup) == "<div lang=\"tr\">Content</div>");
  }
  
  
  SECTION("Nested tags"){
    auto markup1 = div_({}, { nav({}, {}), text("Hello"), hr({}, {})});
    REQUIRE(renderstring(markup1) == "<div><nav></nav>Hello<hr></hr></div>");

    auto markup2 = div_({}, {div_({}, {p({}, {text("a nested paragraph")})})});
    REQUIRE(renderstring(markup2) == "<div><div><p>a nested paragraph</p></div></div>");

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
    REQUIRE(renderstring(markup3) == "<html><head><title>Awesome Website</title><script src=\"/script.js\"></script></head><body><header><img src=\"/logo.png\"></img></header><div>Content Here</div><footer><hr></hr>Copyright 2019</footer></body></html>");
      }
}


TEST_CASE("Abstracting further with the abstractions.", "[ABSTRACTING]"){
  auto li_ = [](std::string item){return li({}, {text(item)});}; 
  auto litems = [=](std::list<std::string> items){
    std::list<Node> result;
    result.resize(items.size());
    std::transform(items.begin(), items.end(), result.begin(), [=](std::string item){ return li_(item);});
    return result;
  };
  auto _ul = [=](std::list<std::string> items){return ul({}, litems(items));}; 
  auto markup = _ul({"Bob", "Mary", "Joe"});
  REQUIRE(renderstring(markup) == "<ul><li>Bob</li><li>Mary</li><li>Joe</li></ul>");


}
