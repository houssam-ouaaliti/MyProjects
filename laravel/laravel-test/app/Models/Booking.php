<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Model;
use Illuminate\Database\Eloquent\Factories\HasFactory;

class Booking extends Model
{
    use HasFactory;

    protected $fillable = [
        'user_id', 
        'property_id', 
        'start_date', 
        'end_date'
    ];

    public function property() {
        return $this->belongsTo(Property::class);
    }

    public function user() {
        return $this->belongsTo(User::class);
    }
}