#include "../catch.hpp"

#include <formal_languages/devices/RegularExpression.hpp>

using namespace formal_device::expression;

TEST_CASE("Regular Expression: Construction of types", "[regular_expression][types]")
{
    SECTION("Regular Expression: Empty", "[regular_expression][empty]")
    {
        Empty a;

        CHECK(a == new Empty());
    }

    SECTION("Regular Expression: RegularPointer", "[regular_expression][regularpointer]")
    {
        RegularPointer p(new Empty());

        CHECK(p == new Empty());
    }

    SECTION("Regular Expression: Epsilon", "[regular_expression][epsilon]")
    {
        Epsilon a;

        CHECK(a == new Epsilon());
    }

    SECTION("Regular Expression: Unit", "[regular_expression][unit]")
    {
        Unit a("a");

        CHECK(a == new Unit("a"));
    }

    SECTION("Regular Expression: Union", "[regular_expression][union]")
    {
        RegularPointer a(new Unit("a"));
        RegularPointer b(new Unit("b"));

        Union un(a, b);

        CHECK( un == new Union(new Unit("a"), new Unit("b")) );
    }

    SECTION("Regular Expression: Concatenation", "[regular_expression][concatenation]")
    {
        RegularPointer a(new Unit("a"));
        RegularPointer b(new Unit("b"));

        Concatenation con(a, b);

        CHECK( con == new Concatenation(new Unit("a"), new Unit("b")) );
    }

    SECTION("Regular Expression: ReflexiveClosure", "[regular_expression][reflexive][closure]")
    {
        RegularPointer a(new Unit("a"));

        ReflexiveClosure reflex(a);

        CHECK( reflex == new ReflexiveClosure(new Unit("a")) );
    }

    SECTION("Regular Expression: TransitiveClosure", "[regular_expression][transitive][closure]")
    {
        RegularPointer a(new Unit("a"));

        TransitiveClosure reflex(a);

        CHECK( reflex == new TransitiveClosure(new Unit("a")) );
    }

    SECTION("Regular Expression: Optional", "[regular_expression][optional]")
    {
        RegularPointer a(new Unit("a"));

        Optional reflex(a);

        CHECK( reflex == new Optional(new Unit("a")) );
    }
}

TEST_CASE("Regular Expression: Empty", "[regular_expression][empty]")
{
    SECTION("Empty: Union", "[regular_expression][empty]")
    {
        RegularPointer empty(new Empty());
        RegularPointer unit(new Unit("a"));

        CHECK((empty | unit)  == unit);
        CHECK((empty | empty) == empty);
    }

    SECTION("Empty: Concatenation", "[regular_expression][empty]")
    {
        RegularPointer empty(new Empty());
        RegularPointer unit(new Unit("a"));

        CHECK((empty + unit) == unit);
    }

    SECTION("Empty: Operation", "[regular_expression][empty]")
    {
        RegularPointer empty(new Empty());

        CHECK((empty ^ Operation::Reflexive)     == empty);
        CHECK((empty ^ Operation::Transitive)     == empty);
        CHECK((empty ^ Operation::Optional) == empty);
    }
}

TEST_CASE("Regular Expression: Unit", "[regular_expression][unit]")
{
    SECTION("Unit: Union", "[regular_expression][unit]")
    {
        RegularPointer a(new Unit("a"));
        RegularPointer b(new Unit("b"));

        RegularPointer ptr = a | b;

        CHECK(ptr == new Union(a, b));

        CHECK((a | new Empty())   == a);
        CHECK((a | new Epsilon()) == new Optional(a));
        CHECK((a | a)             == a);
    }

    SECTION("Unit: Concatenation", "[regular_expression][unit]")
    {
        RegularPointer a(new Unit("a"));
        RegularPointer b(new Unit("b"));

        RegularPointer ptr = a + b;

        CHECK(ptr == new Concatenation(a, b));

        CHECK((a + new Empty())   == a);
        CHECK((a + new Epsilon()) == a);
    }

    SECTION("Empty: Operation", "[regular_expression][unit]")
    {
        RegularPointer a(new Unit("a"));

        CHECK((a ^ Operation::Reflexive)     == new ReflexiveClosure(a));
        CHECK((a ^ Operation::Transitive)     == new TransitiveClosure(a));
        CHECK((a ^ Operation::Optional) == new Optional(a));
    }
}

TEST_CASE("Regular Expression: Union", "[regular_expression][union]")
{
    RegularPointer a(new Unit("a"));
    RegularPointer b(new Unit("b"));

    SECTION("Union: Union", "[regular_expression][union]")
    {
        RegularPointer un(new Union(a, b));

        CHECK((un | a)             == new Union(un, a));
        CHECK((un | new Empty())   == un);
        CHECK((un | new Epsilon()) == new Optional(un));
        CHECK((un | un)            == un);
    }

    SECTION("Union: Concatenation", "[regular_expression][union]")
    {
        RegularPointer un(new Union(a, b));

        CHECK((un + a)             == new Concatenation(un, a));
        CHECK((un + new Empty())   == un);
        CHECK((un + new Epsilon()) == un);
    }

    SECTION("Union: Operation", "[regular_expression][union]")
    {
        RegularPointer un(new Union(a, b));

        CHECK((un ^ Operation::Reflexive)     == new ReflexiveClosure(un));
        CHECK((un ^ Operation::Transitive)     == new TransitiveClosure(un));
        CHECK((un ^ Operation::Optional) == new Optional(un));
    }
}

TEST_CASE("Regular Expression: Concatenation", "[regular_expression][concatenation]")
{
    RegularPointer a(new Unit("a"));
    RegularPointer b(new Unit("b"));

    SECTION("Concatenation: Union", "[regular_expression][concatenation]")
    {
        RegularPointer conc(new Concatenation(a, b));

        CHECK( (conc | a) == new Union(conc, a));

        CHECK((conc | new Empty())   == conc);
        CHECK((conc | new Epsilon()) == new Optional(conc));
        CHECK((conc | conc)          == conc);
    }

    SECTION("Concatenation: Concatenation", "[regular_expression][concatenation]")
    {
        RegularPointer conc(new Concatenation(a, b));

        CHECK((conc + a)             == new Concatenation(conc, a));
        CHECK((conc + new Empty())   == conc);
        CHECK((conc + new Epsilon()) == conc);
    }

    SECTION("Concatenation: Operation", "[regular_expression][concatenation]")
    {
        RegularPointer conc(new Concatenation(a, b));

        CHECK((conc ^ Operation::Reflexive)     == new ReflexiveClosure(conc));
        CHECK((conc ^ Operation::Transitive)     == new TransitiveClosure(conc));
        CHECK((conc ^ Operation::Optional) == new Optional(conc));
    }
}

TEST_CASE("Regular Expression: ReflexiveClosure", "[regular_expression][reflexiveclosure]")
{
    RegularPointer a(new Unit("a"));

    SECTION("ReflexiveClosure: Union", "[regular_expression][reflexiveclosure]")
    {
        RegularPointer reflex(new ReflexiveClosure(a));

        CHECK((reflex | a)             == new Union(reflex, a));
        CHECK((reflex | new Empty())   == reflex);
        CHECK((reflex | new Epsilon()) == reflex);
        CHECK((reflex | reflex)        == reflex);
    }

    SECTION("ReflexiveClosure: Concatenation", "[regular_expression][reflexiveclosure]")
    {
        RegularPointer reflex(new ReflexiveClosure(a));

        CHECK((reflex + a)             == new Concatenation(reflex, a));
        CHECK((reflex + new Empty())   == reflex);
        CHECK((reflex + new Epsilon()) == reflex);
    }

    SECTION("ReflexiveClosure: Operation", "[regular_expression][reflexiveclosure]")
    {
        RegularPointer reflex(new ReflexiveClosure(a));

        CHECK((reflex ^ Operation::Reflexive)     == reflex);
        CHECK((reflex ^ Operation::Transitive)     == reflex);
        CHECK((reflex ^ Operation::Optional) == reflex);
    }
}

TEST_CASE("Regular Expression: TransitiveClosure", "[regular_expression][transitiveclosure]")
{
    RegularPointer a(new Unit("a"));

    SECTION("TransitiveClosure: Union", "[regular_expression][transitiveclosure]")
    {
        RegularPointer trans(new TransitiveClosure(a));

        CHECK((trans | a)             == new Union(trans, a));
        CHECK((trans | new Empty())   == trans);
        CHECK((trans | new Epsilon()) == new ReflexiveClosure(a));
        CHECK((trans | trans)         == trans);
    }

    SECTION("TransitiveClosure: Concatenation", "[regular_expression][transitiveclosure]")
    {
        RegularPointer trans(new TransitiveClosure(a));

        CHECK((trans + a)             == new Concatenation(trans, a));
        CHECK((trans + new Empty())   == trans);
        CHECK((trans + new Epsilon()) == trans);
    }

    SECTION("TransitiveClosure: Operation", "[regular_expression][transitiveclosure]")
    {
        RegularPointer trans(new TransitiveClosure(a));

        CHECK((trans ^ Operation::Reflexive)     == new ReflexiveClosure(a));
        CHECK((trans ^ Operation::Transitive)     == trans);
        CHECK((trans ^ Operation::Optional) == new ReflexiveClosure(a));
    }
}

TEST_CASE("Regular Expression: Optional", "[regular_expression][optional]")
{
    RegularPointer a(new Unit("a"));

    SECTION("Optional: Union", "[regular_expression][optional]")
    {
        RegularPointer opt(new Optional(a));

        CHECK((opt | a)             == new Union(opt, a));
        CHECK((opt | new Empty())   == opt);
        CHECK((opt | new Epsilon()) == opt);
        CHECK((opt | opt)           == opt);
    }

    SECTION("Optional: Concatenation", "[regular_expression][optional]")
    {
        RegularPointer opt(new Optional(a));

        CHECK((opt + a)             == new Concatenation(opt, a));
        CHECK((opt + new Empty())   == opt);
        CHECK((opt + new Epsilon()) == opt);
    }

    SECTION("Optional: Operation", "[regular_expression][optional]")
    {
        RegularPointer opt(new Optional(a));

        CHECK((opt ^ Operation::Reflexive)     == new ReflexiveClosure(a));
        CHECK((opt ^ Operation::Transitive)     == new ReflexiveClosure(a));
        CHECK((opt ^ Operation::Optional) == opt);
    }
}

TEST_CASE("Regular Expression: Construction of DeSimoneTree", "[regular_expression][de_simone]")
{
    SECTION("Regular Expression: Empty", "[regular_expression][empty]")
    {
        Empty a;
        simone_node_ptr unit = a.node_myself();

        const UnitNode * a_ = dynamic_cast<const UnitNode*>(unit);

        CHECK(a_->m_symbol == "Empty");
        CHECK(!a_->m_seam);

        delete unit;
    }

    SECTION("Regular Expression: Epsilon", "[regular_expression][epsilon]")
    {
        Epsilon a;
        simone_node_ptr unit = a.node_myself();

        const UnitNode * a_ = dynamic_cast<const UnitNode*>(unit);

        CHECK(a_->m_symbol == "&");
        CHECK(!a_->m_seam);

        delete unit;
    }

    SECTION("Regular Expression: Unit", "[regular_expression][epsilon]")
    {
        Unit a("a");
        simone_node_ptr unit = a.node_myself();

        const UnitNode * a_ = dynamic_cast<const UnitNode*>(unit);

        CHECK(a_->m_symbol == "a");
        CHECK(!a_->m_seam);

        delete unit;
    }

    SECTION("Regular Expression: Union", "[regular_expression][union]")
    {
        RegularPointer a(new Unit("a"));
        RegularPointer b(new Unit("b"));
        Union un(a, b);

        simone_node_ptr un_ = un.node_myself();

        const UnionNode * union_ = dynamic_cast<const UnionNode*>(un_);
        const UnitNode * a_ = dynamic_cast<const UnitNode*>(union_->m_left);
        const UnitNode * b_ = dynamic_cast<const UnitNode*>(union_->m_right);

        CHECK(a_->m_symbol == "a");
        CHECK(!a_->m_seam);

        CHECK(b_->m_symbol == "b");
        CHECK(!b_->m_seam);

        delete un_;
    }

    SECTION("Regular Expression: Concatenation", "[regular_expression][concatenation]")
    {
        RegularPointer a(new Unit("a"));
        RegularPointer b(new Unit("b"));
        Concatenation con(a, b);

        simone_node_ptr con_ = con.node_myself();

        const ConcatenationNode * concat_ = dynamic_cast<const ConcatenationNode*>(con_);
        const UnitNode * a_ = dynamic_cast<const UnitNode*>(concat_->m_left);
        const UnitNode * b_ = dynamic_cast<const UnitNode*>(concat_->m_right);

        CHECK(a_->m_symbol == "a");
        CHECK(!a_->m_seam);

        CHECK(b_->m_symbol == "b");
        CHECK(!b_->m_seam);

        delete con_;
    }

    SECTION("Regular Expression: ReflexiveClosure", "[regular_expression][reflexive][closure]")
    {
        RegularPointer a(new Unit("a"));
        ReflexiveClosure reflex(a);

        simone_node_ptr reflex_ = reflex.node_myself();

        const ReflexiveNode * reflexive = dynamic_cast<const ReflexiveNode*>(reflex_);
        const UnitNode * a_ = dynamic_cast<const UnitNode*>(reflexive->m_left);

        CHECK(a_->m_symbol == "a");
        CHECK(!a_->m_seam);
        CHECK(!reflexive->m_seam);

        delete reflex_;
    }

    SECTION("Regular Expression: TransitiveClosure", "[regular_expression][transitive][closure]")
    {
        RegularPointer a(new Unit("a"));
        TransitiveClosure trans(a);

        simone_node_ptr trans_ = trans.node_myself();

        const ConcatenationNode * concat = dynamic_cast<const ConcatenationNode*>(trans_);
        const UnitNode * a_ = dynamic_cast<const UnitNode*>(concat->m_left);
        const ReflexiveNode * reflex_ = dynamic_cast<const ReflexiveNode*>(concat->m_right);
        const UnitNode * reflex_unit_ = dynamic_cast<const UnitNode*>(reflex_->m_left);

        CHECK(a_->m_symbol == "a");
        CHECK(!a_->m_seam);

        CHECK(reflex_unit_->m_symbol == "a");
        CHECK(!reflex_unit_->m_seam);

        CHECK(!reflex_->m_seam);

        delete trans_;
    }

    SECTION("Regular Expression: Optional", "[regular_expression][optional]")
    {
        RegularPointer a(new Unit("a"));
        Optional opt(a);

        simone_node_ptr opt_ = opt.node_myself();

        const OptionalNode * optional = dynamic_cast<const OptionalNode*>(opt_);
        const UnitNode * a_ = dynamic_cast<const UnitNode*>(optional->m_left);

        CHECK(a_->m_symbol == "a");
        CHECK(!a_->m_seam);
        CHECK(!optional->m_seam);

        delete opt_;
    }
}
