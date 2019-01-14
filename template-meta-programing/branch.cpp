template<bool cond, typename THEN, typename ELSE>
class IF_;

template<typename THEN, typename ELSE>
class IF_<true, THEN, ELSE> {
    public: typedef THEN value_type;
};

template<typename THEN, typename ELSE>
class IF_<false, THEN, ELSE> {
    public: typedef ELSE value_type;
};

int main() {

    return 0;
}
