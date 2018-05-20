#include "../catch.hpp"

#include <unordered_set>
#include <formal_languages/components/GrammarComponents.hpp>

using namespace formal_device::grammar;

TEST_CASE("Grammar's Symbol", "[grammar][symbol]")
{
    SECTION("Grammar's Symbol:: Default constructor", "[grammar][symbol]"){
        Symbol a;

        CHECK(a == "&");
        CHECK(a.is_terminal());
    }

    SECTION("Grammar's Symbol:: Custom construtors", "[grammar][symbol]"){
        Symbol a("a");

        CHECK(a == "a");
    }

    SECTION("Grammar's Symbol:: Copy construtors", "[grammar][symbol]"){
        Symbol a("a");
        Symbol b(a);

        CHECK(b == "a");
    }

    SECTION("Grammar's Symbol:: Move construtors", "[grammar][symbol]"){
        Symbol a("a");
        Symbol b(std::move(a));

        CHECK(b == "a");
    }

    SECTION("Grammar's Symbol:: Terminal check", "[grammar][symbol]"){
        Symbol a("a");
        Symbol A("A");

        CHECK(a.is_terminal());
        CHECK(!A.is_terminal());
    }

    SECTION("Grammar's Symbol:: Operator ==", "[grammar][symbol]"){
        Symbol a("a");
        Symbol b("a");
        Symbol c("c");

        CHECK(a == b);
        CHECK(!(a == c));
    }
}

TEST_CASE("Sentencial Form", "[grammar][sentencial_form]")
{
    SECTION("Sentencial Form: Custom construtors", "[grammar][sentencial_form]"){
        SentencialForm a("A", "abc");

        CHECK(a.non_terminal() == "A");
        CHECK(a.setence() == "abc");
        CHECK(!a.is_sentence());
    }

    SECTION("Sentencial Form: Copy construtors", "[grammar][sentencial_form]"){
        SentencialForm a("A", "abc");
        SentencialForm b(a);

        CHECK(b.non_terminal() == "A");
        CHECK(b.setence() == "abc");
        CHECK(!b.is_sentence());
    }

    SECTION("Sentencial Form: Move construtors", "[grammar][sentencial_form]"){
        SentencialForm a("A", "abc");
        SentencialForm b(std::move(a));

        CHECK(b.non_terminal() == "A");
        CHECK(b.setence() == "abc");
        CHECK(!b.is_sentence());
    }

    SECTION("Sentencial Form: Sentence check", "[grammar][sentencial_form]"){
        SentencialForm a("A", "abc");
        SentencialForm b(Symbol(), "abc");

        CHECK(!a.is_sentence());
        CHECK(b.is_sentence());
    }

    SECTION("Sentencial Form: Operator ==", "[grammar][sentencial_form]"){
        SentencialForm a("A", "abc");
        SentencialForm b("A", "abc");
        SentencialForm c(Symbol(), "abc");

        CHECK(a == b);
        CHECK(!(a == c));
    }

    SECTION("Sentencial Form: Operator +", "[grammar][sentencial_form]"){
        SentencialForm a("A", "abc");

        a = a + Symbol("b");

        CHECK(a.non_terminal() == "&");
        CHECK(a.setence() == "abcb");
        CHECK(a.is_sentence());

        a = a + Symbol("B");

        CHECK(a.non_terminal() == "B");
        CHECK(a.setence() == "abcb");
        CHECK(!a.is_sentence());
    }
}

TEST_CASE("Sentence Form", "[grammar][sentence]")
{
    SECTION("Sentence Form: Custom construtors", "[grammar][sentence]"){
        Sentence a("abc");

        CHECK(a.setence() == "abc");
        CHECK(a.is_sentence());
    }

    SECTION("Sentence Form: Copy construtors", "[grammar][sentence]"){
        Sentence a("abc");
        Sentence b(a);

        CHECK(b.setence() == "abc");
        CHECK(b.is_sentence());
    }

    SECTION("Sentence Form: Move construtors", "[grammar][sentence]"){
        Sentence a("abc");
        Sentence b(std::move(a));

        CHECK(b.setence() == "abc");
        CHECK(b.is_sentence());
    }

    SECTION("Sentence Form: Sentence check", "[grammar][sentence]"){
        Sentence a("abc");

        CHECK(a.is_sentence());
    }

    SECTION("Sentence Form: Operator ==", "[grammar][sentence]"){
        Sentence a("abc");
        Sentence b("abc");
        Sentence c("bbb");

        CHECK(a == b);
        CHECK(!(a == c));
    }

    SECTION("Sentence: Operator +", "[grammar][sentence]"){
        Sentence a("abc");
        SentencialForm b = a + Symbol("A");

        CHECK(b.non_terminal() == "A");
        CHECK(b.setence() == "abc");
        CHECK(!b.is_sentence());

        b = b + Symbol("b");

        CHECK(b.non_terminal() == "&");
        CHECK(b.setence() == "abcb");
        CHECK(b.is_sentence());
    }

    SECTION("Sentence: static cast", "[grammar][sentence]"){
        SentencialForm a(Symbol(), "abc");

        CHECK(a.is_sentence());

        Sentence* b = static_cast<Sentence*>(&a);

        CHECK(b->setence() == "abc");
        CHECK(b->is_sentence());
        CHECK(a == *b);
    }
}

TEST_CASE("Terminal Production", "[grammar][terminal_production]")
{
    SECTION("Terminal Production: Custom construtors", "[grammar][terminal_production]"){
        TerminalProduction a(Symbol("a"));

        CHECK(a.is_terminal());
    }

    SECTION("Terminal Production: Copy construtors", "[grammar][terminal_production]"){
        TerminalProduction a(Symbol("a"));
        TerminalProduction b(a);

        CHECK(b.is_terminal());
    }

    SECTION("Terminal Production: Move construtors", "[grammar][terminal_production]"){
        TerminalProduction a(Symbol("a"));
        TerminalProduction b(std::move(a));

        CHECK(b.is_terminal());
    }

    SECTION("Terminal Production: Terminal check", "[grammar][terminal_production]"){
        TerminalProduction a(Symbol("a"));

        CHECK(a.is_terminal());
    }

    SECTION("Terminal Production: Operator ==", "[grammar][terminal_production]"){
        TerminalProduction a(Symbol("a"));
        TerminalProduction b(Symbol("a"));
        TerminalProduction c(Symbol("b"));

        CHECK(a == b);
        CHECK(!(a == c));
    }

    SECTION("Terminal Production: Operator <<", "[grammar][terminal_production]"){
        TerminalProduction prod(Symbol("b"));
        SentencialForm b("A", "abc");

        b = prod << b;

        CHECK(b.non_terminal() == "&");
        CHECK(b.setence() == "abcb");
        CHECK(b.is_sentence());
    }

    SECTION("Terminal Production: dynamic cast", "[grammar][terminal_production]"){
        Production* a = new TerminalProduction(Symbol("b"));

        CHECK(a->is_terminal());

        TerminalProduction* b = static_cast<TerminalProduction*>(a);

        CHECK(b->is_terminal());
        CHECK(*b == *a);
        CHECK(*a == *b);

        SentencialForm sent("A", "abc");

        sent = *a << sent;

        CHECK(sent.non_terminal() == "&");
        CHECK(sent.setence() == "abcb");
        CHECK(sent.is_sentence());

        delete a;
    }
}

TEST_CASE("Non-Terminal Production", "[grammar][non_terminal_production]")
{
    SECTION("Non-Terminal Production: Custom construtors", "[grammar][non_terminal_production]"){
        NonTerminalProduction a("a", "A");

        CHECK(!a.is_terminal());
    }

    SECTION("Non-Terminal Production: Copy construtors", "[grammar][non_terminal_production]"){
        NonTerminalProduction a(Symbol("a"), Symbol("A"));
        NonTerminalProduction b(a);

        CHECK(!b.is_terminal());
    }

    SECTION("Non-Terminal Production: Move construtors", "[grammar][non_terminal_production]"){
        NonTerminalProduction a(Symbol("a"), Symbol("A"));
        NonTerminalProduction b(std::move(a));

        CHECK(!b.is_terminal());
    }

    SECTION("Non-Terminal Production: Terminal check", "[grammar][non_terminal_production]"){
        NonTerminalProduction a(Symbol("a"), Symbol("A"));

        CHECK(!a.is_terminal());
    }

    SECTION("Non-Terminal Production: Operator ==", "[grammar][non_terminal_production]"){
        NonTerminalProduction a(Symbol("a"), Symbol("A"));
        NonTerminalProduction b(Symbol("a"), Symbol("A"));
        NonTerminalProduction c(Symbol("b"), Symbol("A"));

        CHECK(a == b);
        CHECK(!(a == c));
    }

    SECTION("Non-Terminal Production: Operator <<", "[grammar][non_terminal_production]"){
        NonTerminalProduction prod(Symbol("b"), Symbol("B"));
        SentencialForm b("A", "abc");

        b = prod << b;

        CHECK(b.non_terminal() == "B");
        CHECK(b.setence() == "abcb");
        CHECK(!b.is_sentence());
    }

    SECTION("Non-Terminal Production: dynamic cast", "[grammar][non_terminal_production]"){
        Production* a = new NonTerminalProduction(Symbol("b"), Symbol("B"));

        CHECK(!a->is_terminal());

        NonTerminalProduction* b = dynamic_cast<NonTerminalProduction*>(a);

        CHECK(!b->is_terminal());
        CHECK(*b == *a);
        CHECK(*a == *b);

        SentencialForm sent("A", "abc");

        sent = *a << sent;

        CHECK(sent.non_terminal() == "B");
        CHECK(sent.setence() == "abcb");
        CHECK(!sent.is_sentence());

        delete a;
    }
}

TEST_CASE("Grammar's Hasher Class", "[grammar][hasher]")
{
    SECTION("Grammar's Symbol:: set", "[grammar][symbol]"){
        Symbol a("a");
        Symbol b("b");


        std::unordered_set<Symbol, Hasher> set;

        set.insert(a);
        set.insert(b);

        CHECK(set.find(a) != set.end());
        CHECK(set.find(b) != set.end());

        CHECK(set.find(Symbol("a")) != set.end());
        CHECK(set.find(Symbol("b")) != set.end());
        CHECK(set.find(Symbol("c")) == set.end());
    }

    SECTION("Grammar's Symbol:: map", "[grammar][symbol]"){
        Symbol a("a");
        Symbol b("b");

        std::unordered_map<Symbol, int, Hasher> map;

        map[a] = 1;
        map[b] = 2;

        CHECK(map.find(a) != map.end());
        CHECK(map.find(b) != map.end());

        CHECK(map[a] == 1);
        CHECK(map[b] == 2);

        CHECK(map.find(Symbol("a")) != map.end());
        CHECK(map.find(Symbol("b")) != map.end());
        CHECK(map.find(Symbol("c")) == map.end());

        CHECK(map[Symbol("a")] == 1);
        CHECK(map[Symbol("b")] == 2);
    }

    SECTION("Production: set", "[grammar][production]"){
        using prod_ptr = ProductionPointer;

        prod_ptr pa(new TerminalProduction(Symbol("a")));
        prod_ptr pb(new NonTerminalProduction("b", "B"));

        SentencialForm sent("B", "abc");

        std::set<prod_ptr> set;

        set.insert(pa);
        set.insert(pb);

        CHECK(set.find(pa) != set.end());
        CHECK(set.find(pb) != set.end());

        prod_ptr pa2(new TerminalProduction(Symbol("a")));
        prod_ptr pb2(new NonTerminalProduction("b", "B"));
        prod_ptr pc(new TerminalProduction(Symbol("c")));

        CHECK(set.find(pa2) != set.end());
        CHECK(set.find(pb2) != set.end());
        CHECK(set.find(pc) == set.end());
    }
}
