#include "../catch.hpp"

#include <formal_languages/components/DeSimoneTreeComponents.hpp>

using namespace formal_device::expression;

TEST_CASE("DeSimoneTreeComponents: Construction of types", "[de_simone_tree][components]")
{
    SECTION("Unit", "[de_simone_tree][components][unit]")
    {
        UnitNode a;

        CHECK(a.m_symbol == "&");
        CHECK(!a.m_seam);
    }

    SECTION("Union", "[de_simone_tree][components][union]")
    {
        UnionNode a;

        CHECK(!a.m_left);
        CHECK(!a.m_right);
    }

    SECTION("Concatenation", "[de_simone_tree][components][concatenation]")
    {
        ConcatenationNode a;

        CHECK(!a.m_left);
        CHECK(!a.m_right);
    }

    SECTION("Reflexive", "[de_simone_tree][components][reflexive]")
    {
        ReflexiveNode a;

        CHECK(!a.m_left);
        CHECK(!a.m_seam);
    }

    SECTION("Optional", "[de_simone_tree][components][ptional]")
    {
        OptionalNode a;

        CHECK(!a.m_left);
        CHECK(!a.m_seam);
    }
}

TEST_CASE("DeSimoneTreeComponents: Seam", "[de_simone_tree][components]")
{
    SECTION("Unit", "[de_simone_tree][components][unit]")
    {
        UnitNode a;
        ReflexiveNode r;

        CHECK(!a.m_seam);

        a.to_sew(&r);
        CHECK(a.m_seam == &r);

        a.to_sew(nullptr);
        CHECK(!a.m_seam);
    }

    SECTION("Union", "[de_simone_tree][components][union]")
    {
        UnionNode union_;
        UnitNode* a = new UnitNode();
        UnitNode* b = new UnitNode();
        ReflexiveNode r;

        union_.m_left = a;
        union_.m_right = b;

        CHECK(!a->m_seam);
        CHECK(!b->m_seam);

        union_.to_sew(&r);
        CHECK(a->m_seam == &union_);
        CHECK(b->m_seam == &r);

        union_.to_sew(nullptr);
        CHECK(a->m_seam == &union_);
        CHECK(!b->m_seam);
    }

    SECTION("Concatenation", "[de_simone_tree][components][concatenation]")
    {
        ConcatenationNode concat;
        UnitNode* a = new UnitNode();
        UnitNode* b = new UnitNode();
        ReflexiveNode r;

        concat.m_left = a;
        concat.m_right = b;

        CHECK(!a->m_seam);
        CHECK(!b->m_seam);

        concat.to_sew(&r);
        CHECK(a->m_seam == &concat);
        CHECK(b->m_seam == &r);

        concat.to_sew(nullptr);
        CHECK(a->m_seam == &concat);
        CHECK(!b->m_seam);
    }

    SECTION("Reflexive", "[de_simone_tree][components][reflexive]")
    {
        ReflexiveNode reflex, reflex_father;
        UnitNode* a = new UnitNode();

        reflex.m_left = a;

        CHECK(!a->m_seam);
        CHECK(!reflex.m_seam);

        reflex.to_sew(&reflex_father);
        CHECK(a->m_seam == &reflex);
        CHECK(reflex.m_seam == &reflex_father);

        reflex.to_sew(nullptr);
        CHECK(a->m_seam == &reflex);
        CHECK(!reflex.m_seam);
    }

    SECTION("Optional", "[de_simone_tree][components][ptional]")
    {
        OptionalNode opt;

        ReflexiveNode r;
        UnitNode* a = new UnitNode();

        opt.m_left = a;

        CHECK(!a->m_seam);
        CHECK(!opt.m_seam);

        opt.to_sew(&r);
        CHECK(a->m_seam == &opt);
        CHECK(opt.m_seam == &r);

        opt.to_sew(nullptr);
        CHECK(a->m_seam == &opt);
        CHECK(!opt.m_seam);
    }
}

TEST_CASE("DeSimoneTreeComponents: Up, down and scape", "[de_simone_tree][components]")
{
    ReflexiveNode root;
    UnionNode* union_ = new UnionNode();
    ConcatenationNode* concat = new ConcatenationNode();
    OptionalNode* opt = new OptionalNode();
    UnitNode* a = new UnitNode();
    UnitNode* b = new UnitNode();
    UnitNode* c = new UnitNode();

    a->m_symbol = "a";
    b->m_symbol = "b";
    c->m_symbol = "c";

    root.m_left = union_;
    union_->m_left = concat;
    union_->m_right = c;
    concat->m_left = a;
    concat->m_right = opt;
    opt->m_left = b;

    root.to_sew(nullptr);

    SECTION("Seam", "[de_simone_tree][components][unit]")
    {
        CHECK(!root.m_seam);
        CHECK(opt->m_seam == union_);
        CHECK(a->m_seam == concat);
        CHECK(b->m_seam == opt);
        CHECK(c->m_seam == &root);
    }
    DeSimoneNode::composition_type composition;

    SECTION("Down q0", "[de_simone_tree][components][unit]")
    {
        DeSimoneNode::node_set_type marked;

        root.down("q0", composition, marked);

        auto end = composition["q0"]["a"].end();

        CHECK(composition["q0"].size() == 3);

        CHECK(composition["q0"]["a"].size() == 1);
        CHECK(composition["q0"]["a"].find(a) != end);

        CHECK(composition["q0"]["c"].size() == 1);
        CHECK(composition["q0"]["c"].find(c) != end);

        CHECK(composition["q0"]["&"].size() == 1);
        CHECK(composition["q0"]["&"].find(nullptr) != end);
    }

    SECTION("q1 by a", "[de_simone_tree][components][unit]")
    {
        DeSimoneNode::node_set_type marked;

        a->up("q1", composition, marked);

        auto end = composition["q1"]["a"].end();

        CHECK(composition["q1"].size() == 4);

        CHECK(composition["q1"]["a"].size() == 1);
        CHECK(composition["q1"]["a"].find(a) != end);

        CHECK(composition["q1"]["b"].size() == 1);
        CHECK(composition["q1"]["b"].find(b) != end);

        CHECK(composition["q1"]["c"].size() == 1);
        CHECK(composition["q1"]["c"].find(c) != end);

        CHECK(composition["q1"]["&"].size() == 1);
        CHECK(composition["q1"]["&"].find(nullptr) != end);
    }

    SECTION("q2 by c", "[de_simone_tree][components][unit]")
    {
        DeSimoneNode::node_set_type marked;

        c->up("q2", composition, marked);

        auto end = composition["q2"]["a"].end();

        CHECK(composition["q2"].size() == 3);

        CHECK(composition["q2"]["a"].size() == 1);
        CHECK(composition["q2"]["a"].find(a) != end);

        CHECK(composition["q2"]["c"].size() == 1);
        CHECK(composition["q2"]["c"].find(c) != end);

        CHECK(composition["q2"]["&"].size() == 1);
        CHECK(composition["q2"]["&"].find(nullptr) != end);
    }

    SECTION("q3 by b", "[de_simone_tree][components][unit]")
    {
        DeSimoneNode::node_set_type marked;

        b->up("q3", composition, marked);

        auto end = composition["q3"]["a"].end();

        CHECK(composition["q3"].size() == 3);

        CHECK(composition["q3"]["a"].size() == 1);
        CHECK(composition["q3"]["a"].find(a) != end);

        CHECK(composition["q3"]["c"].size() == 1);
        CHECK(composition["q3"]["c"].find(c) != end);

        CHECK(composition["q3"]["&"].size() == 1);
        CHECK(composition["q3"]["&"].find(nullptr) != end);
    }
}
