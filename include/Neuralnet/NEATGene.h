#ifndef NEATGENE_H_INCLUDED
#define NEATGENE_H_INCLUDED

struct Gene{
    int flayer;
    int findex;
    int slayer;
    int sindex;
    float weight;
    int innovation;

    Gene(int flayer, int findex, int slayer, int sindex, float weight){
        this->flayer = flayer;
        this->findex = findex;
        this->slayer = slayer;
        this->sindex = sindex;
        this->weight = weight;
    }

    void setInnovation(int i){
        this->innovation = i;
    }

    void display(){
        std::cout<<"Innovation #"<<innovation<<": "<<flayer<<" "<<findex<<" -> "<<slayer<<" "<<sindex<<": wt: "<<weight;
    }
};


#endif // NEATGENE_H_INCLUDED
