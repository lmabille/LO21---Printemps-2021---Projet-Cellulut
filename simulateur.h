
class Simulateur
{
private:
    
    int buffer_config;
    int clock;
    static Simulateur *instance_unique;
    Simulateur();
    Simulateur(const Simulateur &) = delete;
    void operator=(const Simulateur &) = delete;
    static Simulateur *uniqueInstance;

public:
    static Simulateur &donneInstance();
    static void libereInstance();
    void affichage();
    void reset();
    void next();
};
