#ifndef LABEL_CPP
#define LABEL_CPP

#include <label.h>

#include <cstdio>
#include <cstring>

// TODO: lazy buffers updating
namespace GPE
{
    Label& Label::set_text(const char* buf, const size_t& len, const Alignment alignment)
    {
        if(alignment != Alignment::KEEP_OLD) _alignment = alignment;
        // TODO: use the same buffer for all set_text() calls so there will be no allocs
        SingleCharacter* vertices = new SingleCharacter[len]();
        GLuint* indices = new GLuint[len * INDICES_COUNT]();

        unsigned int w_px = 0;
        if(alignment != Alignment::LEFT)
            for(unsigned int c = 0; c < len; c++) w_px += _font->get_char(buf[c]).Advance >> 6;

        // fill VBO
        unsigned int x_px = 0;
        for(unsigned int c = 0; c < len; c++)
        {
            const auto& c_font = _font->get_char(buf[c]);
            SingleCharacter& c_data = vertices[c];

            unsigned int align_px = 0;
            switch(_alignment)
            {
                case Alignment::MIDDLE:
                    align_px = w_px / 2;
                    break;
                case Alignment::RIGHT:
                    align_px = w_px;
                    break;
                case Alignment::KEEP_OLD:
                    printf("Label::set_text():_alignment == Alignment::KEEP_OLD\n");
                default:
                    printf("Label::set_text():_alignment == undefined (how?)\n");
                case Alignment::LEFT:
                    break;
            }
            c_data.top_left.pos = {(long(x_px + c_font.offset.x) - align_px),
                                   c_font.size.y - c_font.offset.y};
            c_data.top_left.tex_pos = {c_font.top_left.x, c_font.top_left.y};
            c_data.top_right.pos = {(long(x_px + c_font.size.x + c_font.offset.x) - align_px),
                                    c_font.size.y - c_font.offset.y};
            c_data.top_right.tex_pos = {c_font.bottom_right.x, c_font.top_left.y};
            c_data.bottom_left.pos = {(long(x_px + c_font.offset.x) - align_px), -c_font.offset.y};
            c_data.bottom_left.tex_pos = {c_font.top_left.x, c_font.bottom_right.y};
            c_data.bottom_right.pos = {(long(x_px + c_font.size.x + c_font.offset.x) - align_px),
                                       -c_font.offset.y};
            c_data.bottom_right.tex_pos = {c_font.bottom_right.x, c_font.bottom_right.y};


            x_px += (c_font.Advance >> 6);
        }

        // fill EBO
        for(unsigned int i = 0, v = 0; i < INDICES_COUNT * len;
            i += INDICES_COUNT, v += VERTICES_COUNT)
        {
            indices[i + 0] = v + 0;  // top_left
            indices[i + 1] = v + 1;  // top_right
            indices[i + 2] = v + 2;  // bottom_left
            indices[i + 3] = v + 1;  // top_right
            indices[i + 4] = v + 3;  // bottom_right
            indices[i + 5] = v + 2;  // bottom_left
        }

        glBindVertexArray(_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(SingleCharacter) * len, vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * len * INDICES_COUNT, indices,
                     GL_STATIC_DRAW);

        _len = len;

        glBindVertexArray(0);
        delete[] vertices;
        delete[] indices;
        return *this;
    }
    Label& Label::set_text(const std::string_view& str, const Alignment alignment)
    {
        return set_text(str.data(), str.size(), alignment);
    }

    Label& Label::set_color(const glm::vec3& color)
    {
        this->color = color;
        return *this;
    }
    Label& Label::set_pos(const glm::vec2& pos)
    {
        this->pos = pos;
        return *this;
    }

    Label::Label(const std::shared_ptr<FontAtlas>& font, const glm::vec2& pos,
                 const glm::vec3& color, const Alignment alignment, const char* buf,
                 const size_t len)
        : color(color), _font(font), pos(pos)
    {
        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &_VBO);
        glGenBuffers(1, &_EBO);

        glBindVertexArray(_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(CharVertex),
                              (void*)offsetof(CharVertex, pos));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(CharVertex),
                              (void*)offsetof(CharVertex, tex_pos));

        if(buf)
            set_text(buf, len ? len : strlen(buf), alignment);
        else
            glBindVertexArray(0);
    }

    void Label::draw(const StaticResources& res, const glm::mat4x4 VP) const
    {
        _font->use();
        res.shader->setMat4("MVP", VP * get_model());
        res.shader->setVec3("textColor", color);
        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, _len * INDICES_COUNT, GL_UNSIGNED_INT, 0);
    }

    glm::mat4x4 Label::get_model() const
    {
        glm::mat4x4 out{1.0f};
        out[3][0] = pos.x;
        out[3][1] = pos.y;
        out[3][2] = 0.0f;
        return out;
    }
}  // namespace GPE
#endif