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

  SECTION("Nested tags"){
    auto markup1 = div_({}, { nav({}, {}), text("Hello"), hr({}, {})});
    REQUIRE(renderstring(markup1) == "<div><nav></nav>Hello<hr></hr></div>");

    auto markup2 = div_({}, {div_({}, {p({}, {text("a nested paragraph")})})});
    REQUIRE(renderstring(markup2) == "<div><div><p>a nested paragraph</p></div></div>");
    /*
    auto markup3 = html({},
			{ head({}, { title({}, {text('Awesome Website')}),
				script({src('/script.js')}, {})}),
			  body({},
			       { header({},
					{ img({src('/logo.png')]) ]),
                      div([], [text('Content Here')]),
                      footer([],
                             [hr([]),
                              text('Copyright 2019')])
                      ])
               ])
    */
  }
}


