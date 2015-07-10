#ifndef ARC_H
#define ARC_H
class Arc {
public:
    Arc(int IDFrom, int IDTo);
    ~Arc();

    int getFrom(void) const;
    int getTo(void) const;

private:
    int from;
    int to;
};
#endif // ARC_H
